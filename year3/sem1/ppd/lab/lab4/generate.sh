#!/bin/bash

output_name="$1"
n=$2
m=$3

output_file=$output_name"$2""$3.txt"

echo "${n} ${m}" > "$output_file"

for ((i=0; i<n; i++)); do
    vector1=()
    for ((j=0; j<m; j++)); do
        vector1+=($((1 + RANDOM % 100)))
    done
    echo "${vector1[*]}" >> "$output_file" 
done