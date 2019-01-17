#!/bin/bash

firstString=$1
file="${firstString/.s/.cor}"

zaz_tmp="/tmp/zaz_output"
my_tmp="/tmp/my_output"

make > /dev/null
./asm $1
mv $file $my_tmp
./zaz_asm $1
mv $file $zaz_tmp

my_hex="/tmp/my_hex"
zaz_hex="/tmp/zaz_hex"
trace="/tmp/asm_trace"

rm -f $trace
rm -f $my_hex
rm -f $zaz_hex

hexdump < $my_tmp > $my_hex
hexdump < $zaz_tmp > $zaz_hex

rm -f $my_tmp
rm -f $zaz_tmp

echo "MY hexdump" > $trace
cat $my_hex >> $trace 
echo "ZAZ hexdump" >> $trace
cat $zaz_hex >> $trace 

if [ ! -f $my_hex ] && [ ! -f $zaz_hex ]
then
	echo "no diff with zaz's asm :)"
else
	diff $my_hex $zaz_hex >> $trace
	let "res = $?"
	if [ $res != 0 ]
	then
		vim $trace
	else
		echo "no diff with zaz's asm :)"
	fi
fi
