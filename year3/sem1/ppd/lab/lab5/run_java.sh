#!/usr/bin/env bash

output_file=$1
output_secv_file="output_secv.txt"
output_par_file="output_par.txt"
secv_name="Secv"
par_name=$2
nSize=(10 1000 10 10000)
mSize=(10 1000 10000 10)
convSize=(3 5 5 5)
pNumber=(1 2 4 8 16)

runtime_par() {

    time_sum=0
    java_file=$1
    java_main=$1
    java_main+=".java"
    no_runs=$2
    javac $java_main

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        start=$(gdate +%s%3N)
        java $java_file $3 $4 $7 $6
        end=$(gdate +%s%3N)

        runtime=$((end-start))
        time_sum=$((runtime + time_sum))

        cmp --silent $7 $5 || echo "different results"
    done

    average=$((time_sum / no_runs))
    return $average
}

runtime_secv() {

    time_sum=0
    java_file=$1
    java_main=$1
    java_main+=".java"
    no_runs=$2
    javac $java_main

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        start=$(gdate +%s%3N)
        java $1 $3 $4 $5
        end=$(gdate +%s%3N)

        runtime=$((end-start))
        time_sum=$((runtime + time_sum))
    done

    average=$((time_sum / no_runs))
    return $average

}

rm $output_file
touch $output_file

for i in ${!nSize[@]}; do
    n="${nSize[$i]}"
    m="${mSize[$i]}"
    conv="${convSize[$i]}"
    dataFile="date$n$m.txt"
    convFile="conv$conv$conv.txt"
    
    echo $n $m
    echo mat $n $m >> $output_file

    runtime_secv $secv_name 10 $dataFile $convFile $output_secv_file
    echo secvential $? >> $output_file

    if [ "$n" -eq 10 ] && [ "$m" -eq 10 ]; then
        runtime_par $par_name 10 $dataFile $convFile $output_secv_file 4 $output_par_file 
        echo threads 4 - $? >> $output_file
    else
        for ((j = 0; j < ${#pNumber[@]}; j++)); do
            no_threads="${pNumber[j]}" 
            runtime_par $par_name 10 $dataFile $convFile $output_secv_file $no_threads $output_par_file 
            echo threads $no_threads  - $? >> $output_file
        done
    fi
    echo "" >> $output_file

done