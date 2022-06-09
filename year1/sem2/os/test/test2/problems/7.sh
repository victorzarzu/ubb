#!/bin/bash

awk '$1 ~ "^t" && $2 ~ "pts/9" {print $1}' last.fake |\
sort | uniq
