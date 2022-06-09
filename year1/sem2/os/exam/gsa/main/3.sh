#!/bin/bash

grep -E "^m" passwd.fake | awk -F: '$3 % 7 == 0 {print $5}'
