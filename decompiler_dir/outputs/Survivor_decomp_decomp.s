.name "Survivor"
.comment "Invincible"

	live	 %1
	fork	 %:label00
	zjmp	 %:label01

label00:
	ld	 %5, r2
	zjmp	 %:label01

label01:
	xor	 r1, r1, r1

label02:
	st	 r2, 1
	live	 %1
	zjmp	 %:label02
