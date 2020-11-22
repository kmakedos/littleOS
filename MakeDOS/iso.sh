#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/makedos.kernel isodir/boot/makedos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "MakeDOS" {
	multiboot /boot/makedos.kernel
}
EOF
grub-mkrescue -o makedos.iso isodir
