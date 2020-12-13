#!/bin/sh
set -e
sudo apt-get install qemu-system
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom makedos.iso
