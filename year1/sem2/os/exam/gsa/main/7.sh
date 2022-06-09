#!/bin/bash

head -n -1 last.fake | grep -E "^t([^ ]+[ ]+){1}pts\/9" | sed -E "s/^([^ ]+)(.*)$/\1/g" | sort | uniq
