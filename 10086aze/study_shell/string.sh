#!/bin/bash
string="abcd"
echo ${string:1:3}
echo ${#string}
if [ $string ]
then
	echo 不为空
else
	echo 为空
fi
