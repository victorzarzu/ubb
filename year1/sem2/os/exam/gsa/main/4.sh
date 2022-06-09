#!/bin/bash

head -n -1 ps.fake | awk 'NR > 1 {print $0}' | sed -E "s/^([^ ]+[ ]+){5}([^ ]+)(.*)$/\2/g" | sort | uniq
