
#!/bin/bash
if [ $# -lt 2 ]
then
	echo "usage: verbosity <champion1> [<champion2><...>]"
else
	zaz_tmp="/tmp/zaz_vm_output"
	my_tmp="/tmp/my_vm_output"

	rm -f $my_tmp
	rm -f $zaz_tmp
	
	make > /dev/null
	
	./corewar -$* > $my_tmp
	../zaz/corewar -v $* > $zaz_tmp
	
	trace="/tmp/vm_trace"
	
	rm -f $trace
	
	if [ ! -f $my_tmp ] && [ ! -f $zaz_tmp ]
	then
		echo "no diff with zaz's asm :)"
	else
		#echo "result for diff \"ours\" - \"zaz's\"\n" > $trace
		diff $my_tmp $zaz_tmp > $trace
		let "res = $?"
		if [ $res != 0 ]
		then
			vim $trace
		else
			echo "no diff with zaz's corewar :)"
		fi
	fi
fi
