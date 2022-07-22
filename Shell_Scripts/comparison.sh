#!/bin/bash
#Program to compare two strings
echo "Enter two strings: "
read str1
read str2
if [[ $str1 == "$str2" ]]
then
    echo "The strings $str1 and $str2 are equal"
else 
    if [[ $str1 < $str2 ]]
    then 
        echo "The string $str2 is greater than $str1"
    else
        echo "The string $str1 is greater than $str2"
    fi
fi