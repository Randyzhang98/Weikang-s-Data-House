#!/bin/zsh
for ((i=0; i<20; i++)); do
    diff out_main/out$i.txt out_a5/out$i.txt > diff/diff$i.txt
    cat diff/diff$i.txt;
        # diff out/out$i.txt ../p4-wty/out/out$i.txt > diff/diff$i.txt
done