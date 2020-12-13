#!/bin/bash
GCC=${GCC-gcc-10.2.0}
BINUTILS=${BINUTILS-binutils-2.35.1}
export PREFIX=${PREFIX-"$HOME/opt/cross"}
export TARGET=${TARGET-i686-elf}
export PATH="$PREFIX/bin:$PATH"


echo "Downloading and installing packages needed for compilation"
sudo apt-get install build-essential make gcc bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo 

if [ ! -d $BINUTILS ]
then
    echo "Downloading and extracting binutils"
    wget https://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.gz
    tar zxvf $BINUTILS.tar.gz 
fi

if [ ! -d $GCC ];
then
    echo "Downloading and extracting gcc"
    wget ftp://ftp.ntua.gr/pub/gnu/gcc/releases/$GCC/$GCC.tar.gz
    tar zxvf $GCC.tar.gz
fi


if [ ! -d build-binutils ]
then 
    echo "Compiling binutils"
    mkdir -p build-binutils
    cd build-binutils
    ../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make -j 6
    make install
    cd ..
fi

if [ ! -d build-gcc ]
then 
    which -- $TARGET-as || echo $TARGET-as is not in the PATH
    echo "Compiling gcc"
    mkdir -p build-gcc
    cd build-gcc
    ../$GCC/configure -target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc -j 6
    make all-target-libgcc -j 6
    make install-gcc
    make install-target-libgcc
    cd ..
fi

echo "Consider exporting the following"
echo 'export PREFIX=${PREFIX-"$HOME/opt/cross"}'
echo 'export TARGET=${TARGET-i686-elf}'
echo 'export PATH="$PREFIX/bin:$PATH"'
echo 'export crossgcc=$TARGET-gcc'
