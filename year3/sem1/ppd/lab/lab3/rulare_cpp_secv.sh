#!/usr/bin/env bash

cpp_file=$1
no_runs=$2
input_file=$3
output_file=$4

time_sum=0
cpp_main=$cpp_file
cpp_main+=".cpp"
clang++ -Wall -std=c++20 $cpp_main -o $cpp_file

for (( i=1 ; i<=$no_runs ; i++ ));
do
  start=$(gdate +%s%3N)
  ./$cpp_file $input_file $output_file
  end=$(gdate +%s%3N)

  runtime=$((end-start))
  echo $runtime

  time_sum=$(($runtime + $time_sum))
done

average=$((time_sum / no_runs))
echo "Average time: " $average "ms"
