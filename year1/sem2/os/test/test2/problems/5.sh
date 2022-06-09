#!/bin/bash

sed -E "s/^([^:]*):(([^:]*:){3})([^:]*):(.*)$/\1:\4/g" passwd.fake |\
awk 'BEGIN{FS = ":"} $1 ~ "88$" {print $2}' 
