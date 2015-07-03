#!/bin/bash

for i in `seq 15 25`
do
    for j in `seq 0 9`
    do
        ./random_in.py $i | ./queue >> data.log
        echo $i $j
    done
done
