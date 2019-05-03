.name "ld"
.comment "DIR | IND,     REG"

label_def_avant:
	## DIR , REG
	ld %0, r1
	ld %-2147483648, r2
	ld %2147483648, r3
	ld %2147483647, r4
	ld %-1, r5
	ld %1, r6
	ld %20, r7
	ld %-20, r8
	ld %:label_def_avant, r9
label_def_au_milieu:
	ld %:label_def_au_milieu, r9
label_def_au_milieu:
	ld %:label_def_au_milieu, r9
	ld %:label_def_apres, r10

## IND , REG
label_def_apres:

label2_def_avant:
	## DIR , REG
	ld 0, r11
	ld -2147483648, r12
	ld 2147483648, r13
	ld 2147483647, r14
	ld -1, r15
	ld 1, r16
	ld 20, r7
	ld -20, r8
	ld :label2_def_avant, r9
label2_def_au_milieu:
	ld :label2_def_au_milieu, r9
label2_def_au_milieu:
	ld :label2_def_au_milieu, r9
	ld :label2_def_apres, r10

## IND , REG
label2_def_apres:
