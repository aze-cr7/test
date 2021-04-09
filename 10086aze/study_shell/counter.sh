#!/bin/bash
echo "智能计算器(aze制作)"
while :
do
read -p "请输入两个整数  " a b
echo "加 --- 1"
echo "减 --- 2"
echo "乘 --- 3"
echo "除 --- 4"
read -p "请选择要执行的运算(1 2 3 4) " count

case $count in
1)printf "%d + %d = %d\n" $a $b `expr $a + $b` ;;
2)printf "%d - %d = %d\n" $a $b `expr $a - $b` ;;
3)printf "%d * %d = %d\n" $a $b `expr $a \* $b` ;;
4)printf "%d / %d = %d\n" $a $b `expr $a / $b` ;;
*)printf "请按指示操作！"
esac
read -p "您是否想继续？（y为继续）" yes
if [ $yes != 'y' ]
then
break
fi
done
