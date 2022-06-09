#!/bin/bash

sed '1i DATE DESPRE PERSONAL' angajati.txt |\
sed  '/49$/d' |\
sed  -E 's/^([a-zA-Z]+)\s([a-zA-Z]+)/\2 \1/g' |\
sed -E '$a TERMINAT'
 
