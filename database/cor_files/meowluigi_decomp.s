.name "Meow Luigi"
.comment "Here we meoooooow !"


label00:
	zjmp	 %:label00
	ld	 %0, r16
	sti	 r1, %:label01, %1
	fork	 %:label05

label01:
	live	 %0
	fork	 %:label06
	zjmp	 %:label01

label02:
	live	 %0
	st	 r15, -200
	st	 r15, -201
	st	 r15, -202
	st	 r15, -203
	st	 r15, -204
	st	 r15, -205
	st	 r15, -206
	st	 r15, -207

label03:
	live	 %0
	st	 r15, -213
	st	 r15, -214
	st	 r15, -215
	st	 r15, -216
	st	 r15, -217
	zjmp	 %:label02

label04:
	live	 %0
	fork	 %:label02
	zjmp	 %:label04

label05:
	live	 %0
	fork	 %:label04
	zjmp	 %:label05

label06:
	sti	 r1, %:label11, %1
	sti	 r1, %:label01, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label08, %1
	sti	 r1, %:label09, %1
	sti	 r1, %:label12, %1
	sti	 r1, %:label05, %1
	sti	 r1, %:label04, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label10, %1
	sti	 r1, %:label10, %6
	sti	 r1, %:label10, %11
	sti	 r1, %:label10, %16
	sti	 r1, %:label10, %21
	sti	 r1, %:label10, %26
	sti	 r1, %:label10, %31
	sti	 r1, %:label10, %36
	sti	 r1, %:label10, %41
	sti	 r1, %:label10, %46
	sti	 r1, %:label10, %51
	sti	 r1, %:label10, %56
	sti	 r1, %:label10, %61
	sti	 r1, %:label10, %66
	sti	 r1, %:label10, %71
	sti	 r1, %:label10, %76
	fork	 %:label05

label07:
	live	 %0
	fork	 %:label11

label08:
	live	 %0
	fork	 %:label09
	zjmp	 %:label08

label09:
	live	 %0
	fork	 %:label10
	zjmp	 %:label09

label10:
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	live	 %42
	zjmp	 %:label10

label11:
	live	 %0
	ld	 %0, r4
	ld	 %8, r5
	ld	 %4, r6
	ld	 %220, r8
	fork	 %:label12
	ld	 %4, r4

label12:
	live	 %0
	ldi	 %:label07, r4, r2
	sti	 r2, %:label13, r4
	add	 r4, r5, r4
	sub	 r4, r8, r16
	zjmp	 %:label13
	sub	 r16, r6, r16
	zjmp	 %:label13
	ld	 %0, r16
	zjmp	 %:label12

label13:
	live	 %0
