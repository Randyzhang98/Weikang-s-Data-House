#!/bin/zsh
for ((i=0; i<67; i++)); do
    ./main -v -t -p -m -g E_A -g E_B -g E_C -g E_D -g E_E -g GOOG < ../testcase/$i.in > out/out$i.txt
done