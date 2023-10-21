#!/bin/bash

n=$1
m=$2

output_file="conv$1""$2.txt"

echo "${n} ${m}" > "$output_file"

for ((i=0; i<n; i++)); do
    vector1=()
    for ((j=0; j<m; j++)); do
        vector1+=($((1 + RANDOM % 10)))
    done
    echo "${vector1[*]}" >> "$output_file" 
done