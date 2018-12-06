#!/bin/bash

make > /dev/null
./asm $1 
./zaz_asm $1

firstString=$1
zazfile="${firstString/.s/.cor}"

myfile="mycor"

zaz_tmp="/tmp/zaz_output"
my_tmp="/tmp/my_output"

my_hex="/tmp/my_hex"
zaz_hex="/tmp/zaz_hex"

trace="/tmp/asm_trace"

mv $myfile $my_tmp
mv $zazfile $zaz_tmp


hexdump < $my_tmp > $my_hex
hexdump < $zaz_tmp > $zaz_hex

echo "MY hexdump" > $trace
cat $my_hex >> $trace 
echo "ZAZ hexdump" >> $trace
cat $zaz_hex >> $trace 


diff $my_hex $zaz_hex >> $trace
let "res = $?"

if [ $res != 0 ]
then
	vim $trace
else
	echo "no diff with zaz's asm :)"
fi
