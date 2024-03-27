#!/bin/sh
g++ bscs22012_hw4.cpp -o qsort
echo -e "\nRandom:"
time ./qsort random
echo -e "\nMedian:"
time ./qsort median