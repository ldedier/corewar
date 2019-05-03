.name "terminator"
.comment "Hasta la vista, baby!"


label00:
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10
	live	 %1
	fork	 %-10

label01:
	zjmp	 %:label00
	ld	 %25, r4
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	st	 r4, -500
	zjmp	 %:label01
