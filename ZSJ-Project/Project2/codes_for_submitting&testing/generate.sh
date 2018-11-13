#!/bin/bash

for i in `seq 0 1`
do
    for j in `seq 1 6`
    do
        ./generate test$i.$j $i $j 6
    done
done 


