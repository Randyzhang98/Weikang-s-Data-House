#!/bin/zsh
# mkdir out_a5
mkdir out_main
for ((i=0; i<20; i++)); do
    # ./a5 < testcase/$i.in > out_a5/out$i.txt
    ./main < testcase/$i.in > out_main/out$i.txt

done