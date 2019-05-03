.name "turtle"
.comment "TURTLE FFS U LAMA"

	sti	 r1, %:label02, %1
	sti	 r1, %:label01, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label00, %1
	ld	 %0, r16
	fork	 %:label02

label00:
	live	 %42
	ld	 %439025904, r2
	ld	 %0, r16
	fork	 %:label03

label01:
	live	 %42
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	st	 r2, -400
	zjmp	 %:label01

label02:
	live	 %42
	zjmp	 %:label02

label03:
	live	 %42
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	st	 r2, 400
	zjmp	 %:label03
