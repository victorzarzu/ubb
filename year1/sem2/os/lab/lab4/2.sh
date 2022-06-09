#!/bin/bash

awk 'NF%2==1 {print $(int(NF/2) + 1)}' 2.txt
