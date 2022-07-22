#!/bin/bash
# Program to print the fibonacci series.
echo "Enter the number of fibonacci numbers to be printed: "
read n
f1=0
f2=1
echo "The first $n fibonacci numbers are: "
echo $f1
echo $f2
for ((i=0; i<=$n; i++))
do
    f3=$((f1+f2))
    echo f3
    f1=$f2
    f2=$f3
done