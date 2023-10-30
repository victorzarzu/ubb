#!/usr/bin/env bash

./run_java.sh times_java_line.txt ParLine
./run_java.sh times_java_col.txt ParCol
./run_java.sh times_java_bloc.txt ParBloc
./run_java.sh times_java_d_lin.txt ParDLin
./run_java.sh times_java_d_col.txt ParDCol
./run_cpp.sh times_col_cpp.txt par_col
./run_cpp.sh times_line_cpp.txt par_line
./run_cpp.sh times_bloc_cpp.txt par_bloc
./run_cpp.sh times_d_lin_cpp.txt par_d_lin
./run_cpp.sh times_d_cyc_cpp.txt par_d_cyc