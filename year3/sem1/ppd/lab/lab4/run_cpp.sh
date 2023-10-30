#!/usr/bin/env bash

output_file=$1
output_secv_file="output_secv.txt"
output_par_file="output_par.txt"
secv_name="secv"
par_name=$2
nSize=(10 1000 10 10000)
mSize=(10 1000 10000 10)
convSize=(3 5 5 5)
pNumber=(2 4 8 16)

runtime() {

    time_sum=0
    cpp_file=$1
    cpp_main=$1
    cpp_main+=".cpp"
    no_runs=$2
    clang++ -Wall -std=c++20 $cpp_main -o $cpp_file

    for (( i=1 ; i<=$no_runs ; i++ ));
    do
        start=$(gdate +%s%3N)
        ./$cpp_file $3 $4 $7 $6
        end=$(gdate +%s%3N)

        runtime=$((end-start))
        time_sum=$((runtime + time_sum))

        cmp --silent $7 $5 || echo "different results"
    done

    average=$((time_sum / no_runs))
    return $average
}

run_secv() {
    cpp_file=$1
    cpp_main=$1
    cpp_main+=".cpp"
    clang++ -Wall -std=c++20 $cpp_main -o $cpp_file

    ./$cpp_file $2 $3 $4
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
        start=$(gdate +%s%3N)
        ./$cpp_file $3 $4 $5
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
    
    ./generate.sh date $n $m
    ./generate_conv.sh $conv $conv

    echo $n $m
    echo mat $n $m >> $output_file
    echo "" >> $output_file

    if [ "$n" -eq 10 ] && [ "$m" -eq 10 ]; then
        runtime_secv $secv_name 10 $dataFile $convFile $output_secv_file
        echo secvential $? >> $output_file
        echo "threads" 4 >> $output_file
        runtime "$par_name""_s" 10 $dataFile $convFile $output_secv_file 4 $output_par_file 
        echo static $? >> $output_file

        runtime "$par_name""_d" 10 $dataFile $convFile $output_secv_file 4 $output_par_file 
        echo dinamic $? >> $output_file
        echo "" >> $output_file
    else
        for ((j = 0; j < ${#pNumber[@]}; j++)); do
            runtime_secv $secv_name 10 $dataFile $convFile $output_secv_file
            echo secvential $? >> $output_file

            no_threads="${pNumber[j]}" 
            echo threads $no_threads >> $output_file
            runtime "$par_name""_s" 10 $dataFile $convFile $output_secv_file $no_threads $output_par_file 
            echo static $? >> $output_file
            runtime "$par_name""_d" 10 $dataFile $convFile $output_secv_file $no_threads $output_par_file 
            echo dinamic $? >> $output_file
            echo "" >> $output_file
        done
    fi

    rm $output_par_file
    rm $output_secv_file
    rm $convFile 
    rm $dataFile 
done