.name "Varimathras"
.comment "If I have wings, why am I always walking?"


label00:
	st	 r1, r9
	live	 %0
	ld	 %656, r1
	ld	 %151162880, r2
	sti	 r1, %:label00, %0
	sti	 r9, %:label00, %4
	sti	 r2, %:label00, %8
	ld	 %0, r1
	ld	 %4, r3
	ld	 %88, r4
	sti	 r9, %:label01, %1
	sti	 r9, %:label02, %1
	sti	 r9, %:label03, %1
	sti	 r9, %:label04, %1

label01:
	live	 %0
	ldi	 %:label01, r1, r2

label02:
	live	 %0
	sti	 r2, %209, r1

label03:
	live	 %0
	add	 r1, r3, r1
	xor	 r1, r4, r16
	zjmp	 %:label05

label04:
	live	 %0
	and	 %0, %0, r16
	zjmp	 %:label01

label05:
	ld	 %0, r1
	and	 %0, %0, r16
	zjmp	 %148
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
	live	 %0
