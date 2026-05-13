#!/bin/bash

# Check whether the entered string is a palindrome
echo "Enter a string:"
read str

rev_str=$(echo "$str" | rev)

if [ "$str" = "$rev_str" ]; then
    echo "$str is a Palindrome."
else
    echo "$str is Not a Palindrome."
fi

# Find factorial of a number
echo "Enter a number:"
read num

fact=1
i=1

while [ $i -le $num ]
do
    fact=$((fact * i))
    i=$((i + 1))
done

echo "Factorial of $num is $fact"