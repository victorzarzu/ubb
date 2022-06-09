#!/bin/bash

grep -o "^r[^ ]*" ps.fake | sort | uniq | sed -E "s/([aeiou])/\1\1/g"
