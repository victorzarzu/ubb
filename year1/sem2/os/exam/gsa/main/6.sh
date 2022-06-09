#!/bin/bash

grep -E "^([^:]+:){2}23[0-9]:" passwd.fake | awk -F: '{print $5}'
