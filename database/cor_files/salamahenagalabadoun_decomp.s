.name "salamahenagalabadoun"
.comment "sussKBO hin hin"

	ld	 32, r3
	ld	 4, r4
	ld	 190, r5
	st	 r1, 6

label00:
	live	 %666
	sti	 r5, r5, r3
	add	 r3, r4, r5
	ld	 %0, r16
	zjmp	 %:label00
