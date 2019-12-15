#!/bin/bash

# Write a header
echo "# Programmes C"

files=`find . -type f -name *.c | sort`

for file in $files
do
    echo "## $file"
    printf "\n\`\`\`c\n"
    cat $file
    printf "\n\`\`\`\n"
done