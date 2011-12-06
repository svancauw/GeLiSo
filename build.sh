#!/bin/bash
if [ -d "../build" ]; then
	echo "../build directory exists and will be empty"
    cd ../build
	rm -r *
else
	echo "../build directory will be created"
	mkdir ../build	
	cd ../build
fi

cmake -DCMAKE_C_COMPILER=/Users/saschavancauwelaert/gcc_461/bin/gcc -DCMAKE_CXX_COMPILER=/Users/saschavancauwelaert/gcc_461/bin/g++ ../GeLiSo/
make -j 2
