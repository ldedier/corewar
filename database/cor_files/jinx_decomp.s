.name "Jinx"
.comment "Stay still, I'm trying to shoot you..!"

	st	 r1, :label03
	st	 r6, -4
	ld	 53, r1

label00:
	ld	 %0, r7
	zjmp	 %:label04

label01:
	live	 %66
	ldi	 %:label01, r3, r1
	sti	 r1, %-173, r3
	add	 r3, r4, r3
	xor	 r5, r3, r6
	zjmp	 %:label02

label02:
	xor	 r3, r3, r3
	zjmp	 %-207

label03:
	st	 r1, r1

label04:
	sti	 r1, %:label05, %1

label05:
	live	 %66
	sti	 r2, %:label00, %-60
	ld	 %4, r4
	st	 r2, 512
	ld	 %48, r5
	sti	 r1, %:label01, %1
	sti	 r1, %:label13, %1
	sti	 r1, %:label06, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label08, %1
	sti	 r1, %:label09, %1
	sti	 r1, %:label10, %1

label06:
	live	 %66

label07:
	live	 %66

label08:
	live	 %66

label09:
	live	 %66

label10:
	live	 %66
	zjmp	 %:label06
	xor	 r3, r3, r3
	sti	 r1, %:label11, %1

label11:
	live	 %66
	fork	 %:label06
	sti	 r1, %:label12, %1
	sti	 r1, %:label12, %9
	sti	 r1, %:label12, %17
	sti	 r1, %:label12, %25

label12:
	live	 %66
	fork	 %:label01
	live	 %66
	fork	 %:label12
	live	 %66
	fork	 %:label13
	live	 %66
	zjmp	 %:label01

label13:
	live	 %66
	ldi	 %:label13, r3, r1
	sti	 r1, %147, r3
	add	 r3, r4, r3
	xor	 r5, r3, r3
	zjmp	 %:label14
	ld	 %0, r7
	zjmp	 %:label14
	ld	 %0, r7
	zjmp	 %:label13

label14:
	xor	 r3, r3, r3
	zjmp	 %113
