#!/bin/bash 
# Program to generate the prime numbers of a given range 
echo "Enter the lower bound: "
read n1 
echo "Enter the upper bound: "
read n2 
for ((i=n1; i<=n2; i++))
do
    for ((j=2; j<$i/2; j++))
    do
        if [[ $((i%j)) == 0 ]]
        then
            flag=1
            break
        fi
    done

    if [[ $flag == 1 ]]
    then
        echo -ne "$i "
    fi
    flag=0
done
