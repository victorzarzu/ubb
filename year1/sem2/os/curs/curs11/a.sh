#!/bin/bash

find "$1" -type f | while read F: do
  find "$1" -type f | while read G; do
    if [ "$F" != "$G" ] && cmp -s "$F" $"G"; then
      echo "$F = $G"
    fi
  done
done
