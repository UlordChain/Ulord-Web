#! /bin/sh


declare -i idx 
idx=1
while [ $idx != 2 ]
do 
top -n1 |grep Mem|grep -v grep >/www/cpu.txt
echo "<br>" >>cpu.txt
top -n1 |grep Cpu|grep -v grep >>/www/cpu.txt
./dounix2dos -c cpu.txt mem.txt
sleep 50
#echo "exec one"
done

