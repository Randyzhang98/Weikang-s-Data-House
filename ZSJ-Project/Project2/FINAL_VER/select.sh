#!/bin/bash

for i in `seq 0 1`
do
    for j in `seq 1 6`
    do
        ./main < test$i.$j.half > result$i.$j.1.half
        ./main < test$i.$j.half > result$i.$j.2.half
        ./main < test$i.$j.half > result$i.$j.3.half
        ./main < test$i.$j.half > result$i.$j.4.half
        ./main < test$i.$j.half > result$i.$j.5.half
        ./main < test$i.$j.zero > result$i.$j.1.zero
        ./main < test$i.$j.zero > result$i.$j.2.zero
        ./main < test$i.$j.zero > result$i.$j.3.zero
        ./main < test$i.$j.zero > result$i.$j.4.zero
        ./main < test$i.$j.zero > result$i.$j.5.zero
        ./main < test$i.$j.last > result$i.$j.1.last
        ./main < test$i.$j.last > result$i.$j.2.last
        ./main < test$i.$j.last > result$i.$j.3.last
        ./main < test$i.$j.last > result$i.$j.4.last
        ./main < test$i.$j.last > result$i.$j.5.last
    done
done 
