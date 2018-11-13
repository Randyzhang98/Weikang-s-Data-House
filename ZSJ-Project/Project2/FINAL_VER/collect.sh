#!/bin/bash

for i in `seq 0 1`
do
    touch result$i.zero
    for j in `seq 1 6`
    do
        cat result$i.$j.1.zero >> result$i.zero
        cat result$i.$j.2.zero >> result$i.zero
        cat result$i.$j.3.zero >> result$i.zero
        cat result$i.$j.4.zero >> result$i.zero
        cat result$i.$j.5.zero >> result$i.zero
        echo $i$i$i$i$i$i$i$i >> result$i.zero
    done
done 