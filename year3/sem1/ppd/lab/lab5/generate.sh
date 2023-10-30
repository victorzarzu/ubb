#!/usr/bin/env bash

nSize=(10 1000 10 10000 10000)
mSize=(10 1000 10000 10 10000)
convSize=(3 5 5 5)

for i in ${!nSize[@]}; do
    n="${nSize[$i]}"
    m="${mSize[$i]}"
    dataFile="date$n$m.txt"
    
    ./generate_mat.sh date $n $m
done

for i in ${!convSize[@]}; do
    conv="${convSize[$i]}"
    convFile="conv$conv$conv.txt"
    ./generate_conv.sh $conv $conv
done