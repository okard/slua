#!/usr/bin/env bash

# Check for build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

#enter build directory
cd build

#create make files with cmake
cmake -DCMAKE_BUILD_TYPE=Debug  -G "Unix Makefiles" ..

#make program
make
