#!/bin/bash
# Program to demonstrate the arithmetic operations using case
until [[ $choice == 6 ]] 
do 
    echo "Enter the two numbers on which the arithmetic operations are to be done: "
    read num1 num2
    echo "Enter the operation to be performed: "
    echo "1) Addition"
    echo "2) Subtraction"
    echo "3) Multiplication"
    echo "4) Division"
    echo "5) Modulo (Remainder)"
    echo "6) Exit"
    read choice 
    case "${choice}" in
        1)
            res=$num1+$num2
            operation=Addition
        ;;
        2)
            res=$num1-$num2
            operation=Subtraction
        ;;
        3)
            res=$num1*$num2
            operation=Multiplication
        ;;
        4)
            res=$num1/$num2
            operation=Division
        ;;
        5) 
            res=$num1%$num2
            operation=Modulo
        ;;
        6)
            break
        ;;
        *)
            echo "Wrong Operation chosen, enter again"
        ;;
    esac

    echo "The result of the $operation operation is $res"
done