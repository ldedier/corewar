.name "zork"
.comment "just a basic living prog"

live: live %0		
l2:	ld	%666666,r2
	ld %3, r3
	st r2, 100
	sub r3, r2, r4
	st r4, 2000
	sub r1, r1, r5
	zjmp %:live
#	ld 	%5,r3
#	ld	%:l2,r4

#	sti	r1,%:live,%1
#	and	r1,%0,r1
#live:	live	%1
#	zjmp	%:live
