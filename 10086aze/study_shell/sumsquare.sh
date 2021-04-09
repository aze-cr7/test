#!/bin/bash
echo 计算两数平方和小程序0-100以内
fun ()
{
	return $((`expr $num1\*$num1+$num2\*$num2`))
}
while :
do
	read -p "请输入数字1：" num1
	read -p "请输入数字2：" num2
	printf "%d %d \n" $num1 $num2
	if [[ $num1 -ge 0  &&  $num1 -le 100  &&  $num2 -ge 0  &&  $num2 -le 100  ]]
	then
		fun $num1 $num2
		printf "%d 和 %d 的平方和为 %d \n" $num1 $num2 $?
	else
		echo 请输入0-100内的数	
	fi
	read -p "输入'q'退出,其他继续" qq
	if [ $qq == 'q' ]
	then
		break
	fi
done
