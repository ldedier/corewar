#!/bin/bash

make > /dev/null
./asm $1 > /dev/null
./zaz_asm $1 > /dev/null

firstString=$1
zazfile="${firstString/.s/.cor}"

myfile="mycor"

zaz_tmp="/tmp/zaz_output"
my_tmp="/tmp/my_output"

mv $myfile $my_tmp
mv $zazfile $zaz_tmp

diff $zaz_tmp $my_tmp
let "res = $?"
trace="/tmp/asm_trace"


if [ $res = 1 ]
then
	echo "my .cor:\n" > $trace
	hexdump < $my_tmp >> $trace
	echo "\nzaz .cor:\n" >> $trace
	hexdump < $zaz_tmp >> $trace
	vim $trace
else
	echo "\x1B[32mOK\033[0m :)"
fi
