.name " maxidef "
.comment " module de defense"


label00:
	live	 %0
	zjmp	 %:label01
	st	 r1, 6

label01:
	live	 %66
	ld	 -4, r1
	st	 r2, -14
	ld	 %0, r5
	zjmp	 %:label06

label02:
	zjmp	 %-492

label03:
	live	 %1
	st	 r2, -385
	st	 r4, -386

label04:
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510
	st	 r3, -510

label05:
	live	 %1
	zjmp	 %:label04

label06:
	ld	 %57672703, r3
	sti	 r1, %:label00, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label07, %9
	sti	 r1, %:label08, %1
	sti	 r1, %:label09, %1
	sti	 r1, %:label10, %1
	sti	 r1, %:label05, %1
	sti	 r1, %:label03, %1
	ld	 -71, r2
	ldi	 %:label05, %4, r4
	ld	 %0, r5

label07:
	live	 %1
	fork	 %:label07
	live	 %1
	zjmp	 %:label08

label08:
	live	 %1
	fork	 %:label10

label09:
	live	 %1
	zjmp	 %:label03

label10:
	live	 %1
	zjmp	 %:label02
