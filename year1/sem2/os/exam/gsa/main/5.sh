#!/bin/bash

grep -E "^[a-z]{4}[0-9]{2}88:" passwd.fake | sed -E "s/^([^:]+:){4}([^:]+)(.*)$/\2/g"
