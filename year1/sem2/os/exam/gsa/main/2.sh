#!/bin/bash

head -n -1 last.fake | awk '{print $1 " " $7}' | awk -F'[ :]' '$2 >= 23 {print $1}' | sort | uniq
