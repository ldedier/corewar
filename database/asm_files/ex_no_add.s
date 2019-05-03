.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r1,%:live,%1
live:	live	%1
	zjmp	%:live
