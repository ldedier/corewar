.name "zork"
.comment "just a basic living prog"

l2:	sti	r1,%:live,%1
	and	r1,%0,r1
live:	live	%1
	sti r1, 1, 1
	zjmp	%:live
	sti	r1, 1, 1
