#!/bin/bash

grep -E "^([^ ]+( )*){2}economica" last.fake | awk '$4 ~ /\<Sun\>/ {print $1}' | sort | uniq
