#!/bin/sh

dir=test_champions
dir=../database/cor_files

log_dir=logs
trace="${log_dir}/valgrind_outputs.log"
errors_file_list="${log_dir}/errors_files.log"
tmp_trace=tmp_val_output


error_exit_code=42
valgrind_supps=sdl2_suppressions.supp

green="\033[32m"
red="\033[91m"
eoc="\033[39m"

make > /dev/null 2>&1

#here to discard test of time consuming .cor
black_list=(Car.cor bee_gees.cor mandragore.cor) 

#bee_gees = OK


mkdir -p $log_dir
rm -f $log_dir/*.log

((i=0))
((j=0))
for file in $dir/*.cor;
do
	if [[ ! " ${black_list[@]} " =~ " $(basename $file) " ]]; then
		j=$((j+1))
		echo "processing: valgrind --leak-check=full --error-exitcode=$error_exit_code --suppressions=$valgrind_supps --log-file=$tmp_trace ./corewar $file > /dev/null 2>&1"
		valgrind --leak-check=full --error-exitcode=$error_exit_code --suppressions=$valgrind_supps --log-file=$tmp_trace ./corewar $file > /dev/null 2>&1
		if [ $? -eq $error_exit_code ]
		then
			echo "${red}file $file showed error: adding them to $trace..${eoc}"
			str="trace for $file:"
			len=${#str}
			echo "" >> $trace
			printf '/%.0s' $(seq 1 $len) >> $trace
			echo "" >> $trace
			echo $str >> $trace
			printf '/%.0s' $(seq 1 $len) >> $trace
			echo "" >> $trace
			echo "" >> $trace
			echo "$file" >> $errors_file_list
			cat $tmp_trace >> $trace
			cat $tmp_trace > "${log_dir}/valgrind_tests_$(basename $file).log"
		else
			echo "$green OK for $file $eoc"
			echo ""
			i=$((i+1))
		fi
		rm $tmp_trace
	fi
done
if [ ! -f $trace ]
then
	echo "${green}no valgrind errors at all ! Your vm rocks ($i/$j valgrind tests passed) !${eoc}"
else
	echo "${red}only $i/$j tests passed${eoc}"
	#vim $trace
fi
