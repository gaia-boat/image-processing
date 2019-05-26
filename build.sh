#! /bin/bash

mkdir -p bin
mkdir -p build

cmake -S . -B ./build

make -C ./build/
