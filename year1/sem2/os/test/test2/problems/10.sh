#!/bin/bash

sed -E "s/[^r]//g" passwd.fake | sort | uniq
