.name "King Sombra"
.comment "Crystal empire is mine!"

	fork	 %:label01
	live	 %0
	fork	 %:label02
	ld	 %251658255, r2
	ld	 %1, r12
	ld	 %40, r11
	st	 r1, 11
	st	 r16, -4

label00:
	live	 %0
	st	 r16, -300
	st	 r2, -301
	st	 r2, -302
	sub	 r11, r12, r11
	zjmp	 %:label03
	ld	 %0, r16
	zjmp	 %:label00

label01:
	ld	 %0, r16
	zjmp	 %:label10

label02:
	ld	 %0, r16
	zjmp	 %:label09

label03:
	ldi	 %:label00, %1, r13
	ld	 %0, r16
	st	 r13, 6

label04:
	live	 %0
	fork	 %:label04
	st	 r13, 6
	live	 %0
	fork	 %:label05
	ld	 %190056971, r10
	ld	 %135004416, r7
	ld	 %273, r8
	ld	 %270, r11
	ld	 %0, r12
	fork	 %:label06
	zjmp	 %:label08

label05:
	ld	 %202068999, r10
	st	 r13, r7
	ld	 %276, r8
	ld	 %274, r11
	ld	 %0, r12
	fork	 %:label06
	zjmp	 %:label08

label06:
	zjmp	 %:label07

label07:
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0

label08:
	sti	 r10, r11, r12
	sti	 r7, r8, r12
	live	 %0

label09:
	live	 %0
	ld	 %190055943, r10
	ld	 %84476405, r11
	ld	 %150994956, r3
	ld	 %150994956, r6
	ld	 %26, r7
	ld	 %495, r4
	ld	 %0, r5
	zjmp	 %:label12

label10:
	live	 %0
	ld	 %190055943, r10
	ld	 %84476405, r11
	fork	 %:label11
	ld	 %190055172, r3
	ld	 %190055172, r6
	ld	 %507, r7
	ld	 %24, r4
	ld	 %0, r5
	zjmp	 %:label12

label11:
	live	 %0
	ld	 %84475923, r3
	ld	 %84475923, r6
	ld	 %511, r7
	ld	 %28, r4
	ld	 %0, r5
	zjmp	 %:label12

label12:
	live	 %0
	st	 r10, 511
	st	 r11, 510
	zjmp	 %501
