#!/bin/bash

for i in `seq 0 5`
do
    touch result$i
    for j in `seq 1 6`
    do
        cat result$i.$j.1 >> result$i 
        cat result$i.$j.2 >> result$i 
        cat result$i.$j.3 >> result$i
        cat result$i.$j.4 >> result$i
        cat result$i.$j.5 >> result$i
        echo $i$i$i$i$i$i$i$i >> result$i
    done
done 