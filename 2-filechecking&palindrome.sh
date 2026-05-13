#!/bin/bash

# Read file name
echo "Enter the file name:"
read fname

# Check if file exists
if [ -f "$fname" ]; then
    echo "Number of lines: $(wc -l < "$fname")"
    echo "Number of words: $(wc -w < "$fname")"
    echo "Number of characters: $(wc -c < "$fname")"
else
    echo "File does not exist."
fi

# Read string for palindrome check
echo "Enter a string:"
read str

# Reverse the string
rev_str=$(echo "$str" | rev)

# Check palindrome
if [ "$str" = "$rev_str" ]; then
    echo "\"$str\" is a Palindrome."
else
    echo "\"$str\" is Not a Palindrome."
fi