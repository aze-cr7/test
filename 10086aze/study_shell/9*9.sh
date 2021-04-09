#!/bin/bash
for i in `seq 1 9`
do
	for j in `seq 1 $i`
	do
	printf "%2d*%2d=%2d   " $j $i `expr $i \* $j`
done
	printf "\n"
done
