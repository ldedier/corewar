.name "ld"
.comment "DIR | IND,     REG"

	ld	 %0, r1
	ld	 %-2147483648, r2
	ld	 %-2147483648, r3
	ld	 %2147483647, r4
	ld	 %-1, r5
	ld	 %1, r6
	ld	 %20, r7
	ld	 %-20, r8
	ld	 %-56, r9
	ld	 %0, r9
	ld	 %-7, r9
	ld	 %7, r10
	ld	 0, r11
	ld	 0, r12
	ld	 0, r13
	ld	 -1, r14
	ld	 -1, r15
	ld	 1, r16
	ld	 20, r7
	ld	 -20, r8
	ld	 -40, r9
	ld	 0, r9
	ld	 -5, r9
	ld	 5, r10
