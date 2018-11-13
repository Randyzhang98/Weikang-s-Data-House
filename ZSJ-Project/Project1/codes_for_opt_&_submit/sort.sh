#!/bin/zsh
for i in `seq 1 5`
do
    for j in `seq 1 6`
    do
        ./main_test < test$i.$j > result$i.$j.1
        ./main_test < test$i.$j > result$i.$j.2
        ./main_test < test$i.$j > result$i.$j.3
        ./main_test < test$i.$j > result$i.$j.4
        ./main_test < test$i.$j > result$i.$j.5
    done
done 