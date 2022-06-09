#!/bin/bash

#sed -E "s/^([^ ]*) ([^ ]*[ ]+){5}([^ ]+)(.*)$/\1:\3/g" last.fake |\
#awk 'BEGIN{FS = ":"} $2 >= 23 {print $1}' |\
#sort |\
#uniq

awk 'NF == 10 {print $0}' last.fake |\
#sed -E "s/^([^ ]*) ([^ ]*[ ]+){5}([^ ]+)(.*)$/\1:\3/g" |\
#awk 'BEGIN{FS = ":"} $2 >= 23 {print $1}' |\
#sort |\
#uniq
awk '{print $1":"$7}' | awk 'BEGIN{FS = ":"} $2 >= 23 {print $1}' |\
sort | uniq





