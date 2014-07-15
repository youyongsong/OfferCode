#!/bin/bash
num=8
let "num+=1"
while "$num" <= 50; do
  echo "num is $num"
done
