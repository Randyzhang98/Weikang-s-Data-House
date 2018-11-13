# #!/bin/zsh
# size=(100000 200000 300000 400000 500000 600000)
# for ((i=0; i<2; i++)); do
#     for ((j=0; j<6; j++)); do
#         s=${size[$j+1]}
#         for ((k=0; k<s; k+=$s/10)); do
#             echo 'type' 'is' $i '&' 'size' 'is' $s '&' 'k' 'is' $k
#             for ((m = 0; m<3;m++)); do
#                 echo $i $k | ./test< test$j.$m >> ./outs/$i.$j.$m.out
#             done
#         done
#     done
# done 

for ((r=0;r<1000;r++));do
for ((j=0; j<6; j++)); do
    for ((m = 0; m<3;m++)); do
        echo 3 0 | ./test< test$j.0 >> ./outs/2.$j.$m.out
    done
done
done