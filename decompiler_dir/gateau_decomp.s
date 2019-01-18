.name "🎂"
.comment "🎂"

	ld	 %0, r10
	zjmp	 %:label04

label00:
	live	 %2
	ld	 %251658240, r2
	ld	 %0, r10
	fork	 %:label02

label01:
	st	 r2, 65025
	st	 r2, 65031
	st	 r2, 65037
	st	 r2, 65043
	st	 r2, 65049
	st	 r2, 65055
	st	 r2, 65061
	st	 r2, 65067
	zjmp	 %:label01

label02:
	live	 %2

label03:
	st	 r2, 65065
	st	 r2, 65071
	st	 r2, 65077
	st	 r2, 65083
	st	 r2, 65089
	st	 r2, 65095
	st	 r2, 65101
	zjmp	 %:label03
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

label04:
	st	 r1, 65173
	st	 r16, 65531
	st	 r1, 143
	st	 r16, 65531
	fork	 %:label00
	live	 %2
	fork	 %:label11

label05:
	live	 %2
	fork	 %:label05
	live	 %2
	fork	 %:label06
	or	 r2, %32, r2

label06:
	live	 %2
	fork	 %:label07
	or	 r2, %16, r2

label07:
	live	 %2
	fork	 %:label08
	or	 r2, %8, r2

label08:
	live	 %2
	fork	 %:label09
	or	 r2, %4, r2

label09:
	ldi	 %:label10, r2, r16
	ld	 %0, r15

label10:
	sti	 r16, %64, r2
	sti	 r16, %:label12, r2
	sti	 r16, %:label14, r2
	sti	 r16, %238, r2
	sti	 r16, %296, r2
	sti	 r16, %354, r2
	live	 %2
	live	 %2
	sti	 r16, %402, r2
	sti	 r16, %448, r2
	zjmp	 %442
	live	 %2

label11:
	live	 %2
	ld	 %507, r6
	ld	 %8, r8
	ld	 %139, r10
	fork	 %:label13
	live	 %2
	ld	 %4, r2
	ld	 %101253622, r3
	ld	 %101253622, r5
	ld	 %168362119, r7

label12:
	ld	 %262144, r9
	ld	 %0, r16
	zjmp	 %:label15

label13:
	live	 %2
	ld	 %0, r2
	ld	 %190055682, r3
	ld	 %190056194, r5
	ld	 %190056706, r7
	ld	 %134443017, r9
	ld	 %0, r16

label14:
	zjmp	 %:label15

label15:
	sti	 r3, r2, r6
	zjmp	 %502
