#!/bin/bash

sed -E "s/[a-zA-Z0-9 ]//g" passwd.fake | sort | uniq
