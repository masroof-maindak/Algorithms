#include <fstream>
#include <iostream>

#define ULIMIT 1000000

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0]
				  << " <fileName> <IntendedFileSize (MBs)>\n";
		return 1;
	}

	int fsize = atoi(argv[2]);
	int n	  = (fsize * 1024 * 1024) / sizeof(int32_t);

	std::ofstream f(std::string{argv[1]}, std::ios::out | std::ios::binary);

	if (!f.is_open()) {
		std::cerr << argv[0] << ": Error opening file.\n";
		return 1;
	}

	for (int i = 0; i < n; i++) {
		int32_t x = rand() % ULIMIT;
		f.write((char *)(&x), sizeof(x));
	}

	f.close();
	return 0;
}
