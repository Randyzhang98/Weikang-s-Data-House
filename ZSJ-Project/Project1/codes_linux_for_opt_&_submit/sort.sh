#!/bin/bash
for i in `seq 0 5`
do
    for j in `seq 1 6`
    do
        ./main_test < test$i.$j > result$i.$j.1
        ./main_test < test$i.$j > result$i.$j.2
        ./main_test < test$i.$j > result$i.$j.3
        ./main_test < test$i.$j > result$i.$j.4
        ./main_test < test$i.$j > result$i.$j.5
        ./main_test < test$i.$j.ac > result$i.$j.ac.1
        ./main_test < test$i.$j.ac > result$i.$j.ac.2
        ./main_test < test$i.$j.ac > result$i.$j.ac.3
        ./main_test < test$i.$j.ac > result$i.$j.ac.4
        ./main_test < test$i.$j.ac > result$i.$j.ac.5
        ./main_test < test$i.$j.dc > result$i.$j.dc.1
        ./main_test < test$i.$j.dc > result$i.$j.dc.2
        ./main_test < test$i.$j.dc > result$i.$j.dc.3
        ./main_test < test$i.$j.dc > result$i.$j.dc.4
        ./main_test < test$i.$j.dc > result$i.$j.dc.5
        ./main_test < test$i.$j.sp > result$i.$j.sp.1
        ./main_test < test$i.$j.sp > result$i.$j.sp.2
        ./main_test < test$i.$j.sp > result$i.$j.sp.3
        ./main_test < test$i.$j.sp > result$i.$j.sp.4
        ./main_test < test$i.$j.sp > result$i.$j.sp.5

        echo $i $j
    done
done 

