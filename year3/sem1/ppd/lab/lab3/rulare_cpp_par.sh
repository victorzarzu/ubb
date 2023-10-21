#!/usr/bin/env bash

cpp_file=$1
no_runs=$2
no_threads=$3
input_file=$4
output_file=$5
secv_file=$6

time_sum=0
cpp_main=$cpp_file
cpp_main+=".cpp"
clang++ -Wall -std=c++20 $cpp_main -o $cpp_file

for (( i=1 ; i<=$no_runs ; i++ ));
do
  start=$(gdate +%s%3N)
  ./$cpp_file $input_file $output_file $no_threads
  end=$(gdate +%s%3N)

  runtime=$((end-start))

  echo $runtime

  time_sum=$((runtime + time_sum))

  cmp --silent $secv_file $output_file || echo "Different results"
done

average=$((time_sum / no_runs))
echo "Average time:" $average "ms"
