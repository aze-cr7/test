#!/bin/bash
echo "猜数字（0-99）"
while :			
do
com_n=$[ RANDOM%100+1 ]		#随机生成0-100内的数字并赋值给com_n
n=0				#用于记录猜的次数
while :
do
	read -p "请输入您猜的数" read_n		#从终端读取一个数字
	if [[ $read_n -le 100 || $read_n -ge 1 ]] #判断输入的数据是否为0-100
	then
		let n++		#数据为0-100 猜的次数加1
		if [ $read_n -gt $com_n ]
		then
			echo 太大		#判断两数大小，并给出提示
		elif [ $read_n -lt $com_n  ]
		then
			echo 太小
		else
			echo 恭喜您猜对了	
			echo 您用了$n 次，猜出了数字，打败全国%100的用户！
			break			#猜对跳出当前循环
		fi
	else
		echo 请按指示输入		
		#输入数据不为0-100给出提示，进入下次循环，本次猜数不计入总次数
	fi
done
while :
do
	read -p "您是否要继续？（n为否，y为是）" res	
						#给出提示，让用户自行选择，是否继续
	if [[ $res == 'y' || $res == 'n' ]]	
	#判断用户是否输入正确（y,n），正确->跳出，错误->用户重新输入
	then
		break
	else
		echo 请按指示输入	
	fi
done	
	if [ $res == 'n' ]	#不继续->退出程序；继续->进行下次循环
	then
		break 
	fi
done
