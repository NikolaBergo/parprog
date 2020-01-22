#!bin/bash

echo "-------Without optimization-------"
c++ v1.cpp -o v1
c++ v2.cpp -o v2
c++ v3.cpp -o v3

echo "Naive implementation:"
sudo perf stat -e cache-misses ./v1

echo "Transposed right matrix:"
sudo perf stat -e cache-misses ./v2

echo "Block matrix:"
sudo perf stat -e cache-misses ./v3

echo "------O3 optimization----------"
c++ -O3 v1.cpp -o v1
c++ -O3 v2.cpp -o v2
c++ -O3 v3.cpp -o v3

echo "Naive implementation:"
sudo perf stat -e cache-misses ./v1

echo "Transposed right matrix:"
sudo perf stat -e cache-misses ./v2

echo "Block matrix:"
sudo perf stat -e cache-misses ./v3



