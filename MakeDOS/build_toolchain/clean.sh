#!/bin/bash
GCC=${GCC-gcc-10.2.0}
BINUTILS=${BINUTILS-binutils-2.35.1}

for x in $BINUTILS $GCC build-binutils build-gcc
do
    if [ -d $x ]
    then
        rm -rvf $x*
        
    fi
done
