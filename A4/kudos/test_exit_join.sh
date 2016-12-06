#! usr/bin/env bash

rm store.file
cd userland/
make
cd ..


./kudos/util/tfstool create store.file 16000 disk
./kudos/util/tfstool write store.file userland/join_exit_test join_exit_test
./kudos/util/tfstool write store.file userland/proc proc
./run_qemu.sh join_exit_test
