#!/bin/bash

fisier="input_17.txt"
string=""

for user in $(cat $fisier);do
  string="$user@scs.ubbcluj.ro,$string"
done

echo $string | sed -E "s/,$//"
