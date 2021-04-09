#!/bin/bash
echo "  母牛的故事 "
#一头母牛，每年年初生一头小母牛
#每头小母牛，从第四年开始，每年年初生一头小母牛
#问：第n年有几头母牛？

fun ()
{
	temp=$n
	if [[ $temp -gt 0 && $temp -le 3 ]]
	then
		return $temp
	fi
		res1=`fun $(( temp-1 ))`
		res2=`fun $((temp -2))`
		return $((res1 + res2))
}
read -p "查询的年头》》" n
fun $n
echo "第$n 年有$? 头母牛"
