#!/bin/bash

for user in $(last | head -n -2 | awk '{print $1}' | sort | uniq);do
  touch "4/$user"
  last | head -n -2 | awk -v user=$user 'BEGIN{text = ""} $1 ~ user {text = $3 "\n" text} END{print text}' | sort | uniq > "4/$user"
done
