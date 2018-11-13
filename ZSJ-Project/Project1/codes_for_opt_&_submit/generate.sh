#!/bin/zsh

for i in `seq 1 5`
do
    for j in `seq 1 6`
    do
        ./generate test$i.$j $i $j
    done
done 