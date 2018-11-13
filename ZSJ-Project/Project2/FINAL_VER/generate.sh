#!/bin/bash

for i in `seq 0 1`
do
    for j in `seq 1 6`
    do
        ./generate test$i.$j.zero $i $j 0
        ./generate test$i.$j.half $i $j 1
        ./generate test$i.$j.last $i $j 2
    done
done 


