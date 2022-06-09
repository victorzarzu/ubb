#!/bin/bash

grep -E "economica(.*)Sun" last.fake |\
sed -E "s/([^ ]*) (.*)$/\1/g" |\
sort |\
uniq
