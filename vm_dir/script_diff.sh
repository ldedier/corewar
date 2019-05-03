#!/bin/bash
make > /dev/null

if [ $# -lt 3 ]
then
	echo "usage: ./script_diff champ_folder option depth"
	echo "ex: ./script_diff ../champions 16 2"
	exit 1
fi

trace="/tmp/vm_trace"
zaz_tmp="/tmp/zaz_vm_output"
my_tmp="/tmp/my_vm_output"

champions_folder=$1
option=$2
depth=$3

echo "differing outputs" > $trace

if [ "$depth" -ge 1 ]
then
	((i=0))
	((j=0))
	echo "" >> $trace
	echo "alone champs:" >> $trace

	for filename in $champions_folder/*.cor; do
		rm -f $my_tmp
		rm -f $zaz_tmp
		./corewar -$option $filename > $my_tmp
		../zaz/corewar -v $option $filename > $zaz_tmp
		echo "testing $filename\n"
		j=$((j+1))
		if [ -f $my_tmp ] || [ -f $zaz_tmp ]
		then
			diff --brief $my_tmp $zaz_tmp > /dev/null #HERE TO GET THE DIFFS
			let "res = $?"
			if [ $res != 0 ]
			then
				i=$((i+1))
				echo "diff for: $filename ($option $champions_folder)" >> $trace
			fi
		fi
	done

	if [ "$i" -eq 0 ]
	then
		echo "" >> $trace
		echo "none out of $j 😃 " >> $trace
		echo "" >> $trace
	else
		echo "" >> $trace
		echo "$i champs differs out of $j 😱 " >> $trace
		echo "" >> $trace
	fi
fi
vim $trace
