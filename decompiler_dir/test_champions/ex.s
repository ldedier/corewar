.name "zork"
.comment "justub r3, r2,a basic living prog"

live: live %-1		
l2:	ld	%666666,r2
	sub r3, r2, r4
	ld %20, r4
	st r4, 2000
	sub r1, r1, r5
	live %2
	zjmp %-5
