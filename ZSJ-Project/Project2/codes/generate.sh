#!/bin/bash

for i in `seq 0 1`
do
    for j in `seq 1 7`
    do
        ./generate test$i.$j $i $j 6
    done
done 


