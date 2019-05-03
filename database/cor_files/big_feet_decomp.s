.name "top defense plus plus"
.comment "la meilleure defense c'est d'avoir une bonne defense"


label00:
	ld	 %-16, r5
	ld	 %-12, r4
	ld	 %-8, r6
	ld	 %150994944, r10
	ld	 %42991616, r2
	ld	 %256, r3
	ld	 %16, r16
	ld	 %12, r7
	ld	 %16, r9
	ld	 %20, r11
	ld	 %23, r12
	ld	 %1, r13
	ld	 %0, r8
	sti	 r1, %:label01, %1
	sti	 r1, %:label04, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label03, %1
	fork	 %:label02

label01:
	live	 %-530930513
	sti	 r2, %:label00, r5
	sti	 r3, %:label00, r4
	sti	 r10, %:label00, r6
	sub	 r5, r16, r5
	sub	 r4, r16, r4
	sub	 r6, r16, r6
	sub	 r12, r13, r12
	zjmp	 %:label00
	ld	 %0, r8
	zjmp	 %:label01

label02:
	live	 %13371337
	fork	 %:label01
	live	 %42424242
	fork	 %:label04
	live	 %123456789
	fork	 %:label02
	live	 %-194501935
	fork	 %:label03
	zjmp	 %:label02

label03:
	live	 %1663336123
	zjmp	 %:label02

label04:
	live	 %1713792036
	sti	 r2, %51, r7
	sti	 r3, %45, r9
	sti	 r10, %39, r11
	add	 r7, r16, r7
	add	 r9, r16, r9
	add	 r11, r16, r11
	sub	 r12, r13, r12
	zjmp	 %:label00
	ld	 %0, r8
	zjmp	 %:label04
