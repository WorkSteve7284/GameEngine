#!/bin/bash

if ! command -v g++ >/dev/null 2>&1
then
    echo "Error: G++ is not installed!"
    echo
    echo "On Debian-based distributions, try running"
    echo "sudo apt install g++"
else
    echo "Compiling PotatoEngine compiler!"
    g++ compile.cpp -o pe-compile.elf
fi
