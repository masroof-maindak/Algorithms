Default:
rng:
	g++ generate-random-file.cpp -o rngF
sorter:
	g++ src.cpp -o extS

gen:
	clear && ./rngF random.bin 10
run:
	clear && ./extS random.bin

clean:
	rm -f rngF extS *.bin
