#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

#define eightNums	32 / sizeof(std::uint32_t)
#define halfKBsNums 256 / sizeof(std::uint32_t)
#define oneMBsNums	1024 * 1024 / sizeof(std::uint32_t)
#define tenMBsNums	oneMBsNums * 10

const int chunkSize = tenMBsNums;

struct chunkInfo {
	std::streampos posToRead; // Where this chunk begins
	size_t numsLeft;		  // How many integers are left in this chunk
};

struct bufValue {
	int32_t val;
	size_t chunkIndex;
	bool operator>(const bufValue &other) const { return val > other.val; }
};

void printFile(std::string fileName) {
	std::ifstream out(fileName, std::ios::binary);
	int32_t numInts = 0;
	out.read((char *)&numInts, sizeof(int));

	while (numInts > 0) {
		size_t currChunkSize = std::min(chunkSize, numInts);

		std::vector<int32_t> chunk(currChunkSize);
		out.read((char *)chunk.data(), currChunkSize * sizeof(int32_t));

		for (int j = 0; j < currChunkSize; j++)
			std::cout << chunk[j] << " ";
		numInts -= currChunkSize;
	}

	std::cout << "\n";
	out.close();
}

int produceSortedChunks(std::ifstream &in, std::fstream &out,
						std::vector<chunkInfo> &chunkInfoArr) {
	/* TODO: remove this requirement; read file size instead */
	int numInts = 0;
	in.read((char *)&numInts, sizeof(int));
	out.write((char *)&numInts, sizeof(int));

	size_t numFullChunks = numInts / chunkSize;
	uint8_t imbalance	 = (numInts % chunkSize == 0) ? 0 : 1;
	size_t numChunks	 = numFullChunks + imbalance;

	chunkInfoArr.resize(numChunks);

	int intsLeft = numInts;
	for (int i = 0; i < numChunks; i++) {
		size_t currChunkSize	  = std::min(chunkSize, intsLeft);
		chunkInfoArr[i].posToRead = in.tellg();
		chunkInfoArr[i].numsLeft  = currChunkSize;

		std::vector<int32_t> chunk(currChunkSize);
		in.read((char *)chunk.data(), currChunkSize * sizeof(int32_t));

		std::sort(chunk.begin(), chunk.end());
		out.write((char *)chunk.data(), currChunkSize * sizeof(int32_t));

		intsLeft -= currChunkSize;
	}

	return numChunks;
}

void replenishBuffer(std::vector<std::queue<int>> &buffers,
					 std::vector<chunkInfo> &chunkInfoArr, std::fstream &tmp,
					 size_t subchunkSize, int i) {

	subchunkSize = std::min(subchunkSize, chunkInfoArr[i].numsLeft);
	std::vector<int32_t> subchunk(subchunkSize);

	tmp.seekg(chunkInfoArr[i].posToRead);
	tmp.read((char *)subchunk.data(), subchunkSize * sizeof(int32_t));

	chunkInfoArr[i].posToRead += (subchunkSize * sizeof(int32_t));
	chunkInfoArr[i].numsLeft -= subchunkSize;

	for (int j = 0; j < subchunkSize; j++)
		buffers[i].push(subchunk[j]);
}

/* TODO: refactor down */
void mergeSortedChunks(std::fstream &tmp, std::ostream &out,
					   std::vector<chunkInfo> &chunkInfoArr, size_t numChunks) {
	size_t numInts;
	tmp.seekg(0);
	tmp.read((char *)&numInts, sizeof(int32_t));
	out.write((char *)&numInts, sizeof(int32_t));

	size_t subchunkSize = numInts / chunkSize + 1;

	std::vector<std::queue<int32_t>> buffers(numChunks);
	/* TODO: range-based for loop */
	for (int i = 0; i < buffers.size(); i++)
		replenishBuffer(buffers, chunkInfoArr, tmp, subchunkSize, i);

	int ctr = 0;
	std::vector<int32_t> minVals(subchunkSize);
	std::priority_queue<bufValue, std::vector<bufValue>, std::greater<bufValue>>
		mh;

	for (int i = 0; i < buffers.size(); i++)
		mh.push({buffers[i].front(), (size_t)i});

	while (!mh.empty()) {
		/* 1. Get the smallest value across all the smallest values */
		bufValue minPair = mh.top();
		mh.pop();
		size_t minIdx = minPair.chunkIndex;

		/* 2. Push it to an array of the smallest values, and remove it from its
		 * respective queue */
		minVals[ctr++] = minPair.val;
		buffers[minIdx].pop();

		/* 3. If that buffer is now empty, but has more integers to read, read
		 * them */
		if (buffers[minIdx].empty() and chunkInfoArr[minIdx].numsLeft > 0)
			replenishBuffer(buffers, chunkInfoArr, tmp, subchunkSize, minIdx);

		/* 4. If the buffer is not empty, push its minheap value (i.e first) to
		 * the minheap */
		if (!buffers[minIdx].empty())
			mh.push({buffers[minIdx].front(), minIdx});

		/* 5. If the array of minheap values is full, write to file and reset
		 * the counter */
		if (ctr == subchunkSize) {
			out.write((char *)minVals.data(), ctr * sizeof(int32_t));
			ctr = 0;
		}
	}

	if (ctr > 0)
		out.write((char *)minVals.data(), ctr * sizeof(int32_t));
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
	std::string fileName	 = argv[1];
	std::string tempFileName = "temp-" + fileName;
	std::string newFileName	 = "sorted-" + fileName;

	std::ofstream fileOut;
	std::fstream fileTmp;
	std::ifstream fileIn;

	std::vector<chunkInfo> chunkInfoArr;

	/* TODO: error handling */
	fileIn.open(fileName, std::ios::binary);
	fileTmp.open(tempFileName, std::ios::binary | std::ios::out);
	int numChunks = produceSortedChunks(fileIn, fileTmp, chunkInfoArr);
	fileIn.close();

	fileOut.open(newFileName, std::ios::binary);
	mergeSortedChunks(fileTmp, fileOut, chunkInfoArr, numChunks);
	fileTmp.close();
	fileOut.close();

	printFile(newFileName);

	return 0;
}
