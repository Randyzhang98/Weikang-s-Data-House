#!/bin/zsh
for ((i=0; i<67; i++)); do
    diff out/out$i.txt ../a4-gty/out/out$i.txt > diff/diff$i.txt 
    cat diff/diff$i.txt;
        # diff out/out$i.txt ../p4-wty/out/out$i.txt > diff/diff$i.txt
done