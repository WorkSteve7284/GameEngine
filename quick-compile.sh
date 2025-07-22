#!/bin/bash

clear
cd lib
sh recompile-libs.sh

cd ../compile
sh recompile.sh

cd ..

compile/pe-compile.elf src/main.cpp