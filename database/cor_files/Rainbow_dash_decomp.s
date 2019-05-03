.name "basic"
.comment "this is a basic stuff"


label00:
	st	 r1, 6
	live	 %0
	ld	 %0, r2
	zjmp	 %:label00
