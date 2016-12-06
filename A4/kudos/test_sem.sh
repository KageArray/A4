#! usr/bin/env bash

rm store.file
cd userland/
make
cd ..


./kudos/util/tfstool create store.file 16000 disk
./kudos/util/tfstool write store.file userland/semopenclosetest semopenclosetes
./run_qemu.sh semopenclosetes
