#!/bin/bash
arr=(1 2 3 jkl)
val=${arr[3]}
len=${#arr[@]}
echo $val
echo ${arr[@]}
echo $len

for i in "${arr[@]}"
do
  echo $i
done

for i in "${arr[*]}"; do
    echo $i
done

if [ `test ${arr[1]} -eq ${arr[2]}` ]
then
	echo 1
else
	echo 0
fi
