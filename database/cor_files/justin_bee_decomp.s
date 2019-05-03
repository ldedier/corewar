.name "L'arene des abeilles"
.comment "Baby, baby, baby, oh !"

	sti	 r1, %:label04, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label05, %1
	sti	 r1, %:label00, %1
	sti	 r1, %:label06, %1
	sti	 r1, %:label01, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label08, %1
	ld	 %0, r16
	fork	 %:label04

label00:
	live	 %314
	ld	 %31415926, r2
	ld	 %0, r16
	fork	 %:label05

label01:
	live	 %314
	ld	 %0, r16
	fork	 %:label06

label02:
	ld	 %62821932, r5
	ld	 %0, r16
	fork	 %:label07

label03:
	live	 %314
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	st	 r2, -450
	zjmp	 %:label03

label04:
	live	 %314
	zjmp	 %:label04

label05:
	live	 %314
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	st	 r2, 450
	zjmp	 %:label05

label06:
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	live	 %314
	zjmp	 %:label01

label07:
	zjmp	 %:label08
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500

label08:
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
	st	 r5, 500
