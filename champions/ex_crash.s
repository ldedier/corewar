.name "zork"
.comment "just a basic living prog"

l2:	sti	r1,%:live,%1
	st	r1, 42
	and	r1,%0,r1
live:	live	%3
	zjmp %-25
