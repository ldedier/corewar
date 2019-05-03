.name "Wall"
.comment "Werror(you) Wextra(me)"

	ld	 %1, r14
	zjmp	 %:label04
	st	 r15, -8
	sti	 r1, %:label05, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label04, %1
	sti	 r1, %:label00, %1
	sti	 r1, %:label00, %9
	sti	 r1, %:label01, %1
	sti	 r1, %:label01, %9
	sti	 r1, %:label01, %17

label00:
	live	 %66
	fork	 %:label04
	live	 %66
	fork	 %:label00

label01:
	live	 %-1717986919
	lfork	 %925
	live	 %66
	lfork	 %1941
	live	 %66
	lfork	 %2957

label02:
	live	 %66
	fork	 %:label02
	aff	 r1

label03:
	live	 %66
	ld	 %0, r16
	zjmp	 %:label03

label04:
	live	 %66
	ld	 %42991616, r2
	ld	 %265, r3
	ld	 %-458752, r4
	fork	 %:label04

label05:
	live	 %66
	st	 r2, -300
	st	 r3, -301
	st	 r4, -302
	st	 r2, -303
	st	 r3, -304
	st	 r4, -305
	st	 r2, -306
	st	 r3, -307
	st	 r4, -308
	st	 r2, -309
	st	 r3, -310
	st	 r4, -311
	st	 r2, -312
	st	 r3, -313
	st	 r4, -314
	st	 r2, -315
	st	 r3, -316
	st	 r4, -317
	st	 r2, -318
	st	 r3, -319
	st	 r4, -320
	st	 r2, -321
	st	 r3, -322
	st	 r4, -323
	st	 r2, -324
	st	 r3, -325
	st	 r4, -326
	st	 r2, -327
	st	 r3, -328
	st	 r4, -329
	ld	 %0, r16
	zjmp	 %:label05
