#!/usr/bin/env bash

output_file=$1
output_secv_file="output_secv.txt"
output_par_file="output_par.txt"
secv_name=$2
par_name="$2_par"
nSize=(1000000)
pNumber=(2 4 8 16)

runtime_par() {
    time_sum=0
    cpp_file=$1
    cpp_main=$1
    cpp_main+=".cpp"
    no_runs=$2
    mpic++ $cpp_main -o $cpp_file

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        #start=$(gdate +%s%3N)
        #./$cpp_file $3 $4 $7 $6
        #end=$(gdate +%s%3N)

        #runtime=$((end-start))
        runtime=$(mpirun -np $6 $3 $4 $7 2>&1)
        execution_time=$(echo "$runtime" | awk '/Execution Time:/ {print $3}')
        time_sum=$((execution_time + time_sum))

        cmp --silent $7 $5 || echo "different results"
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
        runtime=$(./$cpp_file $3 $4 $5 2>&1)
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

    runtime_secv_avg=$(runtime_secv $secv_name 10 $dataFile $convFile $output_secv_file)
    echo secvential $runtime_secv_avg >> $output_file
    for ((j = 0; j < ${#pNumber[@]}; j++)); do
        no_threads="${pNumber[j]}" 
        echo processes $no_threads >> $output_file
        runtime_avg=$(runtime_par "$par_name" 10 $dataFile $convFile $output_secv_file $no_threads $output_par_file)
        echo $runtime_avg >> $output_file
    done
    echo "" >> $output_file

    rm $output_par_file
    rm $output_secv_file
done