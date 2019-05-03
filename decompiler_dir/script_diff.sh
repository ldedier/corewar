#!/bin/bash

#cp $1 "/tmp"

asm_file="$1"
cor_file="${asm_file/.s/.cor}"
decomp_asm_file="${asm_file/.s/_decomp.s}"
decomp_cor_file="${decomp_asm_file/.s/.cor}"
decomp_asm_decomp_cor_file="${decomp_asm_file/.s/_decomp.s}"

make -C ../asm_dir > /dev/null
make > /dev/null

#asm="./../asm_dir/asm"
asm="./../zaz/asm"

eval "$asm  $asm_file"
./decompiler  $cor_file
eval "$asm  $decomp_asm_file"
./decompiler  $decomp_cor_file

trace="/tmp/asm_trace"

echo "trace:" > $trace

diff $cor_file $decomp_cor_file >> $trace
let "res1 = $?"
diff $decomp_asm_file $decomp_asm_decomp_cor_file >> $trace
let "res2 = $?"
if [ $res1 != 0 ] || [ $res2 != 0 ]
then
	vim $trace
else
	echo "no diffs at all :)"
	mkdir -p outputs
	mv $cor_file $decomp_asm_file $decomp_cor_file $decomp_asm_decomp_cor_file outputs
	#foo.s -> *asm* -> foo.cor -> *decompiler* -> foo_decomp.s -> *asm* -> foo_decomp.cor -> *decompiler* ->foo_decomp_decomp.s"
	#successfully diffed foo.cor with foo_decomp.cor and foo_decomp.s with foo_decomp_decomp.s"
fi

