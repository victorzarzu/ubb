#!/bin/bash

output_file="$1"

vector_size=$((1 + RANDOM % 99999))

vector1=()
vector2=()

for ((i=0; i<vector_size; i++)); do
  vector1+=($((1 + RANDOM % 100000)))
done

for ((i=0; i<vector_size; i++)); do
  vector2+=($((1 + RANDOM % 100000)))
done

echo "${vector_size}" > "$output_file"
echo "${vector1[*]}" >> "$output_file"
echo "${vector2[*]}" >> "$output_file"