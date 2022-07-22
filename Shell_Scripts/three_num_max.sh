#!/bin/bash
#Program to find the greatest the greatest of the given three numbers
echo "Enter the three numbers: "
read num1 num2 num3

if [[ $num1 > $num2 ]]
then
    largest=$num1
else
    largest=$num2
fi

if [[ $largest < $num3 ]]
then
    largest=$num3
fi

echo "The number $largest is the greatest of the given three numbers"