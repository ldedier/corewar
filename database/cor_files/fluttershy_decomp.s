.name "fluttershy"
.comment "oh, my, what a scary project"

	fork	 %:label05
	st	 r1, 6
	live	 %42
	fork	 %:label13
	st	 r1, 6
	live	 %42
	fork	 %:label08

label00:
	st	 r1, 6

label01:
	live	 %213904
	fork	 %:label01

label02:
	sti	 r1, %:label03, %1
	st	 r1, 6
	live	 %43123
	sti	 r1, %:label04, %1
	ld	 %-6, r2
	ld	 %-6, r3
	ld	 %150994953, r4
	ld	 %-186, r5

label03:
	live	 %295423
	sti	 r4, %:label00, r2
	add	 r2, r3, r2
	sti	 r4, %:label00, r2
	add	 r2, r3, r2

label04:
	live	 %3940641
	xor	 r2, r5, r15
	zjmp	 %:label02
	ld	 %0, r16
	zjmp	 %:label03

label05:
	st	 r1, 6

label06:
	live	 %123012
	fork	 %:label06
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

label07:
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	live	 %985341
	zjmp	 %:label07

label08:
	st	 r1, 6

label09:
	live	 %213904
	fork	 %:label09

label10:
	sti	 r1, %:label11, %1
	st	 r1, 6
	live	 %43123
	sti	 r1, %:label12, %1
	ld	 %0, r2
	ld	 %6, r3
	ld	 %150994953, r4
	ld	 %180, r5

label11:
	live	 %295423
	sti	 r4, %153, r2
	add	 r2, r3, r2
	sti	 r4, %142, r2
	add	 r2, r3, r2

label12:
	live	 %3940641
	xor	 r2, r5, r15
	zjmp	 %:label10
	ld	 %0, r16
	zjmp	 %:label11

label13:
	st	 r1, 6

label14:
	live	 %96824
	fork	 %:label14

label15:
	ld	 %0, r2
	ld	 %4, r3
	ld	 %96, r5
	sti	 r1, %:label17, %1
	st	 r1, 6

label16:
	live	 %8008135
	ldi	 %:label15, r2, r4
	sti	 r4, %400, r2
	add	 r2, r3, r2
	ldi	 %:label15, r2, r4
	sti	 r4, %383, r2
	add	 r2, r3, r2

label17:
	live	 %89523
	xor	 r2, r5, r15
	zjmp	 %362
	ld	 %0, r15
	zjmp	 %:label16
