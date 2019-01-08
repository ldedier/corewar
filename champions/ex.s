.name "zork"
.comment "just a basic living prog"

live: live %-2
l2:	ld	%666666,r2
	aff r2
	ld %3, r3
	sti r2, 1, 5
	sub r3, r2, r4
#	st r2, 2000
#	sub r1, r1, r5
	add r5, r7, r7
	zjmp %:live
#	ld 	%5,r3
#	ld	%:l2,r4

#	sti	r1,%:live,%1
#	and	r1,%0,r1
#live:	live	%1
#	zjmp	%:live
