#!/bin/bash

sed -E "s/^([^:]*:){2}([^:]*):[^:]*:([^:]*):(.*)$/\2:\3/g" passwd.fake |\
awk 'BEGIN{FS = ":"} $1 ~ "23[0-9]" {print $2}'
