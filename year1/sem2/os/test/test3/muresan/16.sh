#!bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

for fisier in $(find $1 -type f);do
  if ls -l $fisier | grep -E -q "^-(.w.){3}";then
    echo $fisier
    chmod u-w,g-w,o-w $fisier
  fi
done
