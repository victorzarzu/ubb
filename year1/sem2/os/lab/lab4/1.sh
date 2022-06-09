#!/bin/bash

awk  'BEGIN{vocale = 0; consoane = 0} $0 ~ /[aeiou]$/{vocale += 1} $0 ~ /[qwrtypsdfghjklzxcvbnm]$/{consoane++} END{printf "%d\n%d", vocale, consoane}' 1.txt
