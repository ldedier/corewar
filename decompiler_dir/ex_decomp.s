.name "zork"
.comment "just a basic living prog"

	sti	 r1, %:label00, %0
	and	 r1, %0, r1

label00:
	live	 %1
	zjmp	 %:label00
