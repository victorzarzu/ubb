#!/bin/bash

sed -E "s/[a-zA-Z0-9 ]//g" passwd.fake |\
#awk -f 9.awk | sort
sort | uniq
