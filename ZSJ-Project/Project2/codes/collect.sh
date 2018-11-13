#!/bin/bash

for i in `seq 0 5`
do
    touch result$i.sp
    for j in `seq 1 6`
    do
        cat result$i.$j.sp.1 >> result$i.sp
        cat result$i.$j.sp.2 >> result$i.sp
        cat result$i.$j.sp.3 >> result$i.sp
        cat result$i.$j.sp.4 >> result$i.sp
        cat result$i.$j.sp.5 >> result$i.sp
        echo $i$i$i$i$i$i$i$i >> result$i.sp
    done
done 