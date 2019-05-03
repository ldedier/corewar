#!/bin/bash

#dir=test_champions
#dir=../champions
#dir=champions
dir=../database/asm_files
#dir=../database/asm_error_files

green="\033[32m"
red="\033[91m"
eoc="\033[39m"

log_dir=diff_logs # WARNING gets deleted recursively

diff_file_list="${log_dir}/diff_files.log"
created_file_list="${log_dir}/created_files.log"
missing_file_list="${log_dir}/missing_files.log"

make >/dev/null 2>&1
make -C ../decompiler_dir >/dev/null 2>&1


my_hex="/tmp/my_hex"
zaz_hex="/tmp/zaz_hex"

mkdir -p $log_dir
rm -rf ${log_dir}/*

black_list=(add.s and.s ldi.s lldi.s or.s sti.s sub.s xor.s)

((i=0))
((j=0))
for file in $dir/*.s;
do
	if [[ ! " ${black_list[@]} " =~ " $(basename $file) " ]]; then
		echo "processing ===> $file <===="
		basename=$(basename $file)
		corfile="${file/.s/.cor}"
		corbasename=$(basename $corfile)
		trace_folder="${log_dir}/${basename/.s/}"
		trace="${trace_folder}/hexdump_trace"
		mkdir -p ${trace_folder}
		head -n 1000 $file  > "$trace_folder/$basename" 2>/dev/null
		zaz_output="${trace_folder}/zaz_$corbasename"
		my_output="${trace_folder}/my_$corbasename"
		j=$((j+1))
		./asm $file >/dev/null 2>&1
		mv $corfile ${my_output} 2>/dev/null
		./zaz_asm $file >/dev/null 2>&1
		mv $corfile ${zaz_output} 2>/dev/null
		if [ ! -f $my_output ] && [ ! -f $zaz_output ] # no asm accepts this .s
		then
			i=$((i+1))
			echo -e "$green OK for $file $eoc"
			rm -rf ${trace_folder}
		elif [ -f $my_output ] && [ -f $zaz_output ] # both asm accepts this .s
		then
			hexdump < $my_output > $my_hex 
			hexdump < $zaz_output > $zaz_hex 
			echo "my hexdump" >> $trace
			cat $my_hex >> $trace 
			echo "zaz hexdump" >> $trace
			cat $zaz_hex >> $trace
			echo "diff:" >> $trace
			diff $my_hex $zaz_hex >> $trace
			if [ $? != 0 ]
			then
				echo -e "${red}file $file showed diff: adding them to $trace..${eoc}"
				echo $file >> $diff_file_list
				../decompiler_dir/decompiler ${zaz_output} >/dev/null 2>&1
				../decompiler_dir/decompiler ${my_output} >/dev/null 2>&1
				zaz_decomp="${zaz_output/.cor/_decomp.s}"
				my_decomp="${my_output/.cor/_decomp.s}"
				decomp_trace=${trace_folder}/decomp_trace
				echo "#########" >> $decomp_trace
				echo "my decomp" >> $decomp_trace
				echo "#########" >> $decomp_trace
				echo "" >> $decomp_trace
				cat $my_decomp >> $decomp_trace
				echo "" >> $decomp_trace
				echo "##########" >> $decomp_trace
				echo "zaz decomp" >> $decomp_trace
				echo "##########" >> $decomp_trace
				echo "" >> $decomp_trace
				cat $zaz_decomp >> $decomp_trace
				echo "" >> $decomp_trace
				echo "#####" >> $decomp_trace
				echo "diff:" >> $decomp_trace
				echo "#####" >> $decomp_trace
				echo "" >> $decomp_trace
				diff $my_decomp $zaz_decomp >> $decomp_trace
			else
				i=$((i+1))
				rm -rf ${trace_folder}
				echo -e "$green OK for $file $eoc"
			fi
		elif [ -f $my_output ]	#our asm compile, zaz's don't
		then
			echo -e "${red}file $file showed diff: adding them to $trace..${eoc}"
			echo $file >> $created_file_list
			../decompiler_dir/decompiler ${my_output}
		else				# zaz's asm compile, our's don't
			echo -e "${red}file $file showed diff: adding them to $trace..${eoc}"
			echo $file >> $missing_file_list
			../decompiler_dir/decompiler -l ${zaz_output}# >/dev/null 2>&1
		fi
	fi
done

if [ ! -f $diff_file_list ]
then
	echo -e "${green}no diffs at all ! Your asm rocks ($i/$j tests passed) !${eoc}"
else
	echo -e "${red}only $i/$j tests passed${eoc}"
fi
