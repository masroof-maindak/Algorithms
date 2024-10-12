#!/bin/sh

g++ src.cpp

echo -e "\nRandom:"
time ./a.out random

echo -e "\nMedian:"
time ./a.out median
