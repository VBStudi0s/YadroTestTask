#!/bin/bash

# Building script for Linux

# Create temp directory for building files
mkdir temp
cd ./temp

# CMake with pointing at neccessary folders
cmake -B./ -S../

# Building
make

# Deleting temp dir
cd ../
rm -r temp
