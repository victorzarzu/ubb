#!/usr/bin/env bash

output_file=$1
output_secv_file="output_secv.txt"
output_par_file="output_par.txt"
secv_name=$2
par_name=$2
par_name+="_par"
dir="./data"
no_countries=5
no_probs=10
pNumber=(4 6 8 16)

runtime_par() {
    time_sum=0
    cpp_file=$1
    cpp_main=$1
    cpp_main+=".cpp"
    no_runs=$2
    clang -std=c++20 $cpp_main -o $cpp_file 2>/dev/null

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        #start=$(gdate +%s%3N)
        #./$cpp_file $3 $4 $7 $6
        #end=$(gdate +%s%3N)

        #runtime=$((end-start))
        runtime=$(./$cpp_file $3 $4 $5 $6 2>&1)
        execution_time=$(echo "$runtime" | awk '/Execution Time:/ {print $3}')
        time_sum=$((execution_time + time_sum))

        cmp --silent $6 $4 || echo "different results"
    done

    average=$((time_sum / no_runs))
    echo $average
}

runtime_secv() {
    time_sum=0
    cpp_file=$1
    cpp_main=$1
    cpp_main+=".cpp"
    clang++ -Wall -std=c++20 $cpp_main -o $cpp_file
    no_runs=$2

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        runtime=$(./$cpp_file $3 $4 2>&1)
        execution_time=$(echo "$runtime" | awk '/Execution Time:/ {print $3}')
        time_sum=$((execution_time + time_sum))
    done

    average=$((time_sum / no_runs))
    echo $average

}

rm $output_file
touch $output_file

for i in ${!nSize[@]}; do
    n="${nSize[$i]}"
    dataFile="date$n.txt"
    
    echo $n
    echo vector $n >> $output_file

    runtime_secv_avg=$(runtime_secv $secv_name 10 $dataFile $output_secv_file)
    echo secvential $runtime_secv_avg >> $output_file
    for ((j = 0; j < ${#pNumber[@]}; j++)); do
        no_threads="${pNumber[j]}" 
        echo processes $no_threads >> $output_file
        runtime_avg=$(runtime_par "$par_name" 10 $dir $no_countries $no_probs $output_par_file)
        echo $runtime_avg >> $output_file
    done
    echo "" >> $output_file

done