#!/bin/bash

luna=$(date | awk '{print $2}')

#for user_count in $(last | head -n -2 | awk '$5 ~ l{print $1}' | sort | uniq -c| sed -E "s/([ ])([0 -9]+)( )/\2,/");do
#  count=$(echo $user_count | cut -d, -f1)
#  user=$(echo $user_count | cut -d, -f2)
#  echo $count $user
#done

for user_count in $(last | head -n -2 | awk -v l=$luna '$5 ~ l{print $1}' | sort | uniq -c | sort -n -r | sed -E "s/^[ ]+([0-9]+) (.*$)/\1,\2/");do
  count=$(echo $user_count | cut -d, -f1)
  user=$(echo $user_count | cut -d, -f2)
  name=$(cat /etc/passwd | grep -E "^$user" | cut -d: -f5 | sed -E "s/([^,]*),.*$/\1/g")

  echo $count $name
done

