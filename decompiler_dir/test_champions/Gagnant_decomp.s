.name "Celebration Funebre v0.99pl42"
.comment "Jour J"

	ld	 %0, r3

label00:
	zjmp	 %80

label01:
	zjmp	 %:label01
	live	 %42

label02:
	sti	 r15, %:label02, r14
	zjmp	 %-200
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

label06:
	sti	 r15, %:label06, r14
	zjmp	 %-200

label07:
	sti	 r15, %:label07, r14
	zjmp	 %-200
	sti	 r1, %-74, %1
	sti	 r1, %-81, %15
	sti	 r1, %-88, %29
	sti	 r1, %-95, %43
	sti	 r1, %-102, %57
	sti	 r1, %-109, %71
	ld	 %393216, r4
	ld	 %917504, r12
	ld	 %1, r11
	ld	 %6, r10
	live	 %42
	sti	 r4, %-155, %1
	add	 r4, r12, r4
	sub	 r10, r11, r10
	zjmp	 %-50
	fork	 %-25
	live	 %3
	fork	 %40
	live	 %4
	fork	 %69
	live	 %42
	ldi	 %8, %-193, r15
	ld	 %-186, r14
	ld	 %0, r2
	zjmp	 %:label00
	live	 %42
	fork	 %61
	live	 %42
	ldi	 %4, %-230, r15
	ld	 %-190, r14
	ld	 %0, r2
	zjmp	 %:label00
	live	 %42
	ldi	 %12, %-259, r15
	ld	 %-182, r14
	ld	 %0, r2
	zjmp	 %:label00
	live	 %42

label08:
	ldi	 %:label08, %-288, r15
	ld	 %-194, r14
	ld	 %0, r2
