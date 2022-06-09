#!/bin/bash

for user in $(ps -ef | awk 'NR > 1{print $1}' | sort | uniq);do
  echo -n $user" "
  ps -u $user | awk 'BEGIN{sum = 0; nr = 0} NR > 1{sum += $1; nr++} END{if(nr > 0){print sum/nr} else {print 0}}'
done
