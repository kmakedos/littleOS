#!/bin/bash -x
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
mkdir -p $HOME/opt/cross
if  [ -z ${BINUTILS_DIR} ]; 
then
    echo "BINUTILS_DIR not set"
    exit 1
fi

if [ -z ${GCC_DIR} ];
then 
    echo "GCC_DIR not set"
    exit 1
fi

rm -rf build-binutils
rm -rf build-gcc
rm -rf third_party/*
