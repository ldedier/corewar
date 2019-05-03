.name "Xx_DaRk_SaSuKe_93_xX"
.comment "The Dirty Hamster"

	st	 r1, 235
	st	 r1, 205
	ld	 %8, r15
	ld	 %1, r16
	ld	 %-400, r13
	ld	 %0, r11
	ld	 %0, r16
	zjmp	 %:label00
	live	 %9999999
	lfork	 %-5

label00:
	ld	 -3, r9
	ld	 -13, r7
	ld	 -17, r8
	ld	 %300, r10
	fork	 %:label04
	live	 %999999
	fork	 %:label03
	ld	 %0, r16
	zjmp	 %:label01

label01:
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	st	 r1, 58
	ld	 %0, r16

label02:
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	live	 %93999
	zjmp	 %:label02

label03:
	live	 %9999999
	sub	 r13, r15, r13
	sti	 r9, r10, r13
	ld	 %0, r16
	zjmp	 %:label03

label04:
	live	 %9999999
	add	 r11, r15, r11
	sti	 r7, r10, r11
	sti	 r8, r10, r11
	ld	 %0, r16
	zjmp	 %:label04
