#!/bin/bash
# Program to find the largest of the given array of numbers
echo "Enter the size of the array: "
read n
declare -A arr 
for ((i=0; i<n; i++))
do
    read arr["$i"]
done

max=${arr[$i]}
for ((i=1; i<n; i++))
do
    if [[ $max < ${arr[$i]} ]]
    then 
        max=${arr[$i]}
    fi
done

echo "The largest of the given numbers is $max"
