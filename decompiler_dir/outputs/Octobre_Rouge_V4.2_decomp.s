.name "Octobre Rouge V4.2"
.comment "And the winner is ..."

	st	 r1, 19
	ld	 %0, r15
	fork	 %:label00
	zjmp	 %:label10

label00:
	live	 %42
	fork	 %:label10
	zjmp	 %:label00

label01:
	live	 %42
	fork	 %:label03
	st	 r1, 13
	ld	 %0, r15

label02:
	live	 %42
	zjmp	 %:label02

label03:
	live	 %42
	fork	 %:label05
	st	 r1, 13
	ld	 %0, r15

label04:
	live	 %42
	zjmp	 %:label04

label05:
	live	 %42
	fork	 %:label07
	st	 r1, 13
	ld	 %0, r15

label06:
	live	 %42
	zjmp	 %:label06

label07:
	live	 %42
	fork	 %:label01
	st	 r1, 13
	ld	 %0, r15

label08:
	live	 %42
	zjmp	 %:label08

label09:
	live	 %42
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	ld	 %0, r15
	zjmp	 %:label09

label10:
	live	 %42
	fork	 %:label11
	live	 %42
	fork	 %:label12
	live	 %42
	fork	 %:label13
	ld	 %57672448, r3
	ld	 %318992390, r6
	ld	 %0, r15
	zjmp	 %:label14

label11:
	live	 %42
	fork	 %:label10
	live	 %42
	fork	 %:label01
	ld	 %251883526, r3
	ld	 %386101254, r6
	ld	 %0, r15
	ld	 %0, r15
	zjmp	 %:label14

label12:
	live	 %42
	fork	 %:label09
	ld	 %-65214, r3
	ld	 %436432902, r6
	ld	 %0, r15
	ld	 %0, r15
	ld	 %0, r15
	zjmp	 %:label14

label13:
	st	 r1, r3
	ld	 %251883526, r6
	ld	 %0, r15
	ld	 %0, r15
	ld	 %0, r15
	ld	 %0, r15
	zjmp	 %:label14

label14:
	st	 r3, 15
	st	 r6, -1
	live	 %42
