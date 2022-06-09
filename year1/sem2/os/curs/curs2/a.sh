#!/bin/bash

echo Command: $0
echo First four args: $1 $2 $3 $4
echo ALl args: $@
echo Arg count: $#

true
echo Command true exited with code $?

false
echo Command false exited with code $?

for A in a b c d; do
  echo Here is $A
done

for A in a b c d
do
  echo Here is $A
done

for A in $@; do
  echo $A
done

for A; do
  echo Arg: $A
done


