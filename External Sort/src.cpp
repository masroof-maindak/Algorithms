#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

constexpr size_t EIGHT_NUMS		 = 32 / sizeof(std::uint32_t);
constexpr size_t INTS_IN_HALF_KB = 256 / sizeof(std::uint32_t);
constexpr size_t INTS_IN_1MB	 = 1024 * 1024 / sizeof(std::uint32_t);
constexpr size_t CHUNK_SIZE		 = INTS_IN_1MB * 10;

struct ChunkInfo {
	std::streampos pos_to_read; // Where this chunk begins
	size_t nums_left;			// How many integers are left in this chunk
};

struct BufValue {
	int32_t val;
	size_t chunkIndex;
	bool operator>(const BufValue &other) const { return val > other.val; }
};

void print_file(std::string file_name) {
	std::ifstream out(file_name, std::ios::binary);
	int32_t n = 0;
	out.read((char *)&n, sizeof(int));

	while (n > 0) {
		size_t curr_chunk_size = std::min(static_cast<int32_t>(CHUNK_SIZE), n);

		std::vector<int32_t> chunk(curr_chunk_size);
		out.read((char *)chunk.data(), curr_chunk_size * sizeof(int32_t));

		for (int j = 0; j < curr_chunk_size; j++)
			std::cout << chunk[j] << " ";

		n -= curr_chunk_size;
	}

	std::cout << "\n";
	out.close();
}

int produce_sorted_chunks(std::ifstream &in, std::fstream &out,
						  std::vector<ChunkInfo> &chunk_info_arr) {
	// TODO: Fix to calculate number of integers from file-size instead
	int n = 0;
	in.read((char *)&n, sizeof(int));
	out.write((char *)&n, sizeof(int));

	size_t num_full_chunks = n / CHUNK_SIZE;
	uint8_t imbalance	   = (n % CHUNK_SIZE == 0) ? 0 : 1;
	size_t num_chunks	   = num_full_chunks + imbalance;

	chunk_info_arr.resize(num_chunks);

	size_t ints_left = n;
	for (int i = 0; i < num_chunks; i++) {
		size_t curr_chunk_size		  = std::min(CHUNK_SIZE, ints_left);
		chunk_info_arr[i].pos_to_read = in.tellg();
		chunk_info_arr[i].nums_left	  = curr_chunk_size;

		std::vector<int32_t> chunk(curr_chunk_size);
		in.read((char *)chunk.data(), curr_chunk_size * sizeof(int32_t));

		std::sort(chunk.begin(), chunk.end());
		out.write((char *)chunk.data(), curr_chunk_size * sizeof(int32_t));

		ints_left -= curr_chunk_size;
	}

	return num_chunks;
}

void replenish_buffer(std::vector<std::queue<int>> &buffers,
					  std::vector<ChunkInfo> &chunk_info_arr, std::fstream &tmp,
					  size_t subchunk_size, int i) {

	subchunk_size = std::min(subchunk_size, chunk_info_arr[i].nums_left);
	std::vector<int32_t> subchunk(subchunk_size);

	tmp.seekg(chunk_info_arr[i].pos_to_read);
	tmp.read((char *)subchunk.data(), subchunk_size * sizeof(int32_t));

	chunk_info_arr[i].pos_to_read += (subchunk_size * sizeof(int32_t));
	chunk_info_arr[i].nums_left -= subchunk_size;

	for (int j = 0; j < subchunk_size; j++)
		buffers[i].push(subchunk[j]);
}

/* TODO: refactor down */
void merge_sorted_chunks(std::fstream &tmp, std::ostream &out,
						 std::vector<ChunkInfo> &chunk_info_arr,
						 size_t num_chunks) {
	size_t numInts;
	tmp.seekg(0);
	tmp.read((char *)&numInts, sizeof(int32_t));
	out.write((char *)&numInts, sizeof(int32_t));

	size_t subchunk_size = numInts / CHUNK_SIZE + 1;

	std::vector<std::queue<int32_t>> buffers(num_chunks);
	/* TODO: range-based for loop */
	for (int i = 0; i < buffers.size(); i++)
		replenish_buffer(buffers, chunk_info_arr, tmp, subchunk_size, i);

	int ctr = 0;
	std::vector<int32_t> min_vals(subchunk_size);
	std::priority_queue<BufValue, std::vector<BufValue>, std::greater<BufValue>>
		mh;

	for (int i = 0; i < buffers.size(); i++)
		mh.push({buffers[i].front(), (size_t)i});

	while (!mh.empty()) {
		/* 1. Get the smallest value across all the smallest values */
		BufValue min_pair = mh.top();
		mh.pop();
		size_t min_idx = min_pair.chunkIndex;

		/* 2. Push it to an array of the smallest values, and remove it from its
		 * respective queue */
		min_vals[ctr++] = min_pair.val;
		buffers[min_idx].pop();

		/* 3. If that buffer is now empty, but has more integers to read, read
		 * them */
		if (buffers[min_idx].empty() and chunk_info_arr[min_idx].nums_left > 0)
			replenish_buffer(buffers, chunk_info_arr, tmp, subchunk_size,
							 min_idx);

		/* 4. If the buffer is not empty, push its minheap value (i.e first) to
		 * the minheap */
		if (!buffers[min_idx].empty())
			mh.push({buffers[min_idx].front(), min_idx});

		/* 5. If the array of minheap values is full, write to file and reset
		 * the counter */
		if (ctr == subchunk_size) {
			out.write((char *)min_vals.data(), ctr * sizeof(int32_t));
			ctr = 0;
		}
	}

	if (ctr > 0)
		out.write((char *)min_vals.data(), ctr * sizeof(int32_t));
}

int main(int argc, char **argv) {
	std::ios::ios_base::sync_with_stdio(0);
	std::cout.tie(NULL);
	std::cin.tie(NULL);

	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << "<file_name>\n";
		return 1;
	}

	/* TODO: eliminate temp file */

	std::string fname	  = argv[1];
	std::string tmp_fname = "temp-" + fname;
	std::string new_fname = "sorted-" + fname;

	std::ofstream f_out;
	std::fstream f_tmp;
	std::ifstream f_in;

	std::vector<ChunkInfo> chunk_info_arr;

	/* TODO: error handling */
	f_in.open(fname, std::ios::binary);
	f_tmp.open(tmp_fname, std::ios::binary | std::ios::out);
	int num_chunks = produce_sorted_chunks(f_in, f_tmp, chunk_info_arr);
	f_in.close();

	f_out.open(new_fname, std::ios::binary);
	merge_sorted_chunks(f_tmp, f_out, chunk_info_arr, num_chunks);
	f_tmp.close();
	f_out.close();

	print_file(new_fname);

	return 0;
}
