#!/bin/bash

#parametr ALL czyści wszystko
tools/clean.sh $1
mkdir bin
cd bin
cmake -G "Unix Makefiles" --graphviz=../CMake_trash/ARCH.dot ../
. ../CMake_trash/make_wrapper_script.sh
make
cd ..

