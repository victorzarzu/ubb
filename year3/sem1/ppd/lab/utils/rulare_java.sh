#!/usr/bin/env bash

fisier_java=$1
no_runs=$2
input_file=$3
output_file=$4

time_sum=0
java $fisier_java + ".java"

for i in {1..$no_runs}; do
  echo "Rulare $i"
  start=`date +%s`
  time=java $fisier_java $input_file $output_file
  end=`date +%s`

  runtime=$((end-start))
  
  time_sum=$(($runtime + $time_sum))
done

average=$((sum / no_runs))
echo "Average time: " $average
