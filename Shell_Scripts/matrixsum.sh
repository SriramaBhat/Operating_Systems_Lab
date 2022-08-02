#!/bin/bash 
# Program to read two matrices and compute their sums

echo "Enter the order of the first matrix: "
read row1 col1
echo "Enter the ordder of the second matrix: "
read row2 col2
declare -A mat1
declare -A mat2
declare -A mat3

if [[ $col1 == "$col2" && $row1 == "$row2" ]]
then
    echo "Enter the first matrix: "
    for ((i=0; i<row1; i++))
    do
        for ((j=0; j<col1; j++))
        do
            read mat1[$((i*col1+j))]
            mat3[$((i*col1+j))]=${mat1[$((i*col1+j))]}
        done
    done

    echo "Enter the second matrix: "
    for ((i=0; i<row1; i++))
    do
        for ((j=0; j<col1; j++))
        do
            read mat2[$((i*col1+j))]
            mat3[$((i*col1+j))]=$((${mat3[$((i*col1+j))]}+${mat2[$((i*col1+j))]}))
        done
    done

    echo "The resultant matrix is: "
    for ((i=0; i<row1; i++))
    do
        for ((j=0; j<col1; j++))
        do
            echo -ne "${mat3[$((i*col1+j))]} "
        done
        echo
    done
fi
