.name "🎂"
.comment "🎂"


label00:
	ld	 %0, r10
	zjmp	 %:label05

label01:
	live	 %2
	ld	 %251658240, r2
	ld	 %0, r10
	fork	 %:label03

label02:
	st	 r2, -511
	st	 r2, -505
	st	 r2, -499
	st	 r2, -493
	st	 r2, -487
	st	 r2, -481
	st	 r2, -475
	st	 r2, -469
	zjmp	 %:label02

label03:
	live	 %2

label04:
	st	 r2, -471
	st	 r2, -465
	st	 r2, -459
	st	 r2, -453
	st	 r2, -447
	st	 r2, -441
	st	 r2, -435
	zjmp	 %:label04
	ld	 %71, r1
	aff	 r1
	ld	 %82, r1
	aff	 r1
	ld	 %79, r1
	aff	 r1
	ld	 %83, r1
	aff	 r1
	ld	 %32, r1
	aff	 r1
	ld	 %83, r1
	aff	 r1
	ld	 %65, r1
	aff	 r1
	ld	 %67, r1
	aff	 r1
	ld	 %32, r1
	aff	 r1
	ld	 %71, r1
	aff	 r1
	ld	 %82, r1
	aff	 r1
	ld	 %79, r1
	aff	 r1
	ld	 %83, r1
	aff	 r1
	ld	 %32, r1
	aff	 r1
	ld	 %83, r1
	aff	 r1
	ld	 %65, r1
	aff	 r1
	ld	 %67, r1
	aff	 r1
	ld	 %32, r1
	aff	 r1
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	lfork	 %0
	live	 %2

label05:
	st	 r1, :label00
	st	 r16, :label05

label06:
	st	 r1, 143
	st	 r16, :label06
	fork	 %:label01
	live	 %2
	fork	 %:label13

label07:
	live	 %2
	fork	 %:label07
	live	 %2
	fork	 %:label08
	or	 r2, %32, r2

label08:
	live	 %2
	fork	 %:label09
	or	 r2, %16, r2

label09:
	live	 %2
	fork	 %:label10
	or	 r2, %8, r2

label10:
	live	 %2
	fork	 %:label11
	or	 r2, %4, r2

label11:
	ldi	 %:label12, r2, r16
	ld	 %0, r15

label12:
	sti	 r16, %64, r2
	sti	 r16, %:label14, r2
	sti	 r16, %:label16, r2
	sti	 r16, %238, r2
	sti	 r16, %296, r2
	sti	 r16, %354, r2
	live	 %2
	live	 %2
	sti	 r16, %402, r2
	sti	 r16, %448, r2
	zjmp	 %442
	live	 %2

label13:
	live	 %2
	ld	 %507, r6
	ld	 %8, r8
	ld	 %139, r10
	fork	 %:label15
	live	 %2
	ld	 %4, r2
	ld	 %101253622, r3
	ld	 %101253622, r5
	ld	 %168362119, r7

label14:
	ld	 %262144, r9
	ld	 %0, r16
	zjmp	 %:label17

label15:
	live	 %2
	ld	 %0, r2
	ld	 %190055682, r3
	ld	 %190056194, r5
	ld	 %190056706, r7
	ld	 %134443017, r9
	ld	 %0, r16

label16:
	zjmp	 %:label17

label17:
	sti	 r3, r2, r6
	zjmp	 %502
