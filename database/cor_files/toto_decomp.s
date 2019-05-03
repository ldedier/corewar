.name "Celebration Funebre v0.99pl42"
.comment "Jour J"

	ld	 %0, r3

label00:
	zjmp	 %:label09

label01:
	zjmp	 %:label01

label02:
	live	 %42

label03:
	sti	 r15, %:label03, r14
	zjmp	 %-200
	live	 %42

label04:
	sti	 r15, %:label04, r14
	zjmp	 %-200
	live	 %42

label05:
	sti	 r15, %:label05, r14
	zjmp	 %-200
	live	 %42

label06:
	sti	 r15, %:label06, r14
	zjmp	 %-200

label07:
	sti	 r15, %:label07, r14
	zjmp	 %-200

label08:
	sti	 r15, %:label08, r14
	zjmp	 %-200

label09:
	sti	 r1, %:label02, %1
	sti	 r1, %:label02, %15
	sti	 r1, %:label02, %29
	sti	 r1, %:label02, %43
	sti	 r1, %:label02, %57
	sti	 r1, %:label02, %71

label10:
	ld	 %393216, r4
	ld	 %917504, r12
	ld	 %1, r11
	ld	 %6, r10

label11:
	live	 %42
	sti	 r4, %:label00, %1
	add	 r4, r12, r4
	sub	 r10, r11, r10
	zjmp	 %:label10
	fork	 %:label11
	live	 %3
	fork	 %:label12
	live	 %4
	fork	 %:label13
	live	 %42
	ldi	 %8, %-193, r15
	ld	 %-186, r14
	ld	 %0, r2
	zjmp	 %:label00

label12:
	live	 %42
	fork	 %:label14
	live	 %42
	ldi	 %4, %-230, r15
	ld	 %-190, r14
	ld	 %0, r2
	zjmp	 %:label00

label13:
	live	 %42
	ldi	 %12, %-259, r15
	ld	 %-182, r14
	ld	 %0, r2
	zjmp	 %:label00

label14:
	live	 %42

label15:
	ldi	 %:label15, %-288, r15
	ld	 %-194, r14
	ld	 %0, r2
	zjmp	 %:label00
