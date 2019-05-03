.name    "sebc"
.comment "sebc"


l2:
	st	r1, :l1
	ld	%4, r3
l1:	live	%1
	ld	%:l1, r2
l3:	ldi	%:l2, r2, r4
	sti	r4, %:l2, r2
	add	r2, r3, r2
live:	zjmp	%:l1
	xor	r4, r4, r4
	zjmp	%:l3
