.name "Booster !"
.comment "Alors la, si ca marche, trop content !  :)"

	ld	 %12, r2
	ld	 %3, r3
	ld	 %4, r4
	ld	 %5, r7
	sti	 r1, %:label00, %1

label00:
	live	 %66
	sti	 r1, %:label01, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label09, %1
	sti	 r1, %:label04, %1
	sti	 r1, %:label05, %1
	sti	 r1, %:label06, %1
	sti	 r1, %:label07, %-4
	ldi	 %:label07, %-2, r6

label01:
	live	 %66
	fork	 %:label05

label02:
	live	 %66
	fork	 %:label06

label03:
	live	 %66

label04:
	live	 %66
	ld	 %0, r3
	ld	 %16777216, r6
	ld	 %0, r5
	zjmp	 %:label08

label05:
	live	 %66
	ld	 %3, r3
	ld	 %68436, r2
	ld	 %0, r5
	zjmp	 %:label08

label06:
	live	 %66
	ld	 %6, r3
	ld	 %1409680135, r6
	ld	 %0, r5
	zjmp	 %:label08
	sti	 r6, r3, r5

label07:
	sti	 r1, r5, r5

label08:
	sti	 r6, r3, %14

label09:
	live	 %66
	zjmp	 %:label10

label10:
	zjmp	 %:label09
