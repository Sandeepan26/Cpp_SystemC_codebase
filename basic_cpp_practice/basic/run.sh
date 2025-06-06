#!/usr/bin/sh
g++ -std=c++20 "$1" -o "${1%.*}.out"
./${1%.*}.out
echo "Shell Script: Compilation and Execution successful"
