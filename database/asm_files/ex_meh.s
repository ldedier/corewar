.name "ff"
.comment "just a basic living prog"

l2:	sti	r1,r4,r2
and	r10,r2,r5
live:	live	%1
	zjmp	%:live
