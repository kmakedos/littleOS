## CREATE A CROSS COMPILER

### Compile binutils
1. Download binutils
2. export PREFIX="$HOME/opt/cross"
3. export TARGET=i686-elf
4. export PATH="$PREFIX/bin:$PATH"
5. ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
6. make
7. make install

### Compile gcc
1. which -- $TARGET-as || echo $TARGET-as is not in the PATH
2. ../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
3. if it complains about gmp or other stuff: ./contrib/download_prerequisites.sh
3. make all-gcc
4. make all-target-libgcc
5. make install-gcc
6. make install-target-libgcc
