#!/bin/bash -x
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
export MAKE_CPU="${MAKE_CPU:-6}"
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


mkdir build-binutils
cd build-binutils
../$BINUTILS_DIR/configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j $MAKE_CPU
make install
cd ..

which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir build-gcc
cd build-gcc
../$GCC_DIR/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j $MAKE_CPU
make all-target-libgcc -j $MAKE_CPU
make install-gcc
make install-target-libgcc
cd ..
