.name "zork"
.comment "I'M ALIIIIVE"

	sti	 r1, %:label00, %1
	and	 r1, %0, r1

label00:
	live	 %1
	zjmp	 %:label00
