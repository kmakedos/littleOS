#!/bin/bash -x
boot_name=${1%%.asm}.bin
nasm -f bin $1 -o $boot_name
qemu-system-x86_64 $boot_name

