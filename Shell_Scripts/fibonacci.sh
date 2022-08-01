#!/bin/bash
# Program to print the fibonacci series.
echo "Enter the number of fibonacci numbers to be printed: "
read n
f1=0
f2=1
f3=0
echo "The first $n fibonacci numbers are: "
for ((i=1; i<=$n; i++))
do
    echo "    $f3"
    f1=$f2
    f2=$f3
    f3=$((f1+f2))
done
