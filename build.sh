#! /bin/bash

mkdir -p bin
mkdir -p build

cmake -H. -B./build

make -C ./build/
