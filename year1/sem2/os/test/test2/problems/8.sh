#!/bin/bash

awk '$1 ~ "^r" {print $1}' ps.fake | sort | uniq |\
sed -E "s/([aeiouAEIOU])/\1\1/g"
