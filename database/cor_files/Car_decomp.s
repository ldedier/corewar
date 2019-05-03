.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

	fork	 %:label03
	ld	 %-272, r3
	live	 %0
	fork	 %:label01
	ld	 %-272, r3
	fork	 %:label00
	ld	 %0, r2
	ld	 %0, r4
	zjmp	 %:label07

label00:
	ld	 %4, r2
	ld	 %0, r4
	zjmp	 %:label07

label01:
	ld	 %-202, r3
	fork	 %:label02
	ld	 %0, r2
	ld	 %0, r4
	zjmp	 %:label09

label02:
	ld	 %4, r2
	ld	 %0, r4
	zjmp	 %:label09

label03:
	ld	 %400, r3
	live	 %0
	fork	 %:label05
	fork	 %:label04
	ld	 %0, r2
	ld	 %0, r4
	zjmp	 %:label08

label04:
	ld	 %4, r2
	ld	 %0, r4
	zjmp	 %:label08

label05:
	fork	 %:label06
	ld	 %0, r4
	zjmp	 %:label10

label06:
	ld	 %0, r4
	zjmp	 %:label11

label07:
	ldi	 r2, %18, r6
	ld	 %0, r4
	live	 %1
	sti	 r6, r2, r3
	zjmp	 %-277

label08:
	ldi	 r2, %18, r6
	ld	 %0, r4
	live	 %1
	sti	 r6, r2, r3
	zjmp	 %395

label09:
	ldi	 r2, %18, r6
	ld	 %0, r4
	live	 %1
	sti	 r6, r2, r3
	zjmp	 %-207

label10:
	live	 %1
	fork	 %:label10
	zjmp	 %:label10

label11:
	live	 %1
	fork	 %:label11
	zjmp	 %:label11
