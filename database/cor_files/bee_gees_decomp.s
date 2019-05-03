.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"

	sti	 r1, %:label03, %1
	sti	 r1, %:label01, %1
	ld	 %1, r3
	ld	 %33, r6

label00:
	add	 r2, r3, r2
	xor	 r2, %15, r4

label01:
	live	 %4
	zjmp	 %:label02
	fork	 %:label00
	ld	 %0, r4
	zjmp	 %:label00

label02:
	ld	 %0, r4

label03:
	live	 %4
	zjmp	 %:label03
