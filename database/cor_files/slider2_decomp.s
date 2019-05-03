.name "Sliders"
.comment "And the winner is ..."

	sti	 r1, %:label05, %1
	sti	 r1, %:label01, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label08, %1

label00:
	sti	 r1, %:label09, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label11, %1
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
	sti	 r1, %:label10, %81
	sti	 r1, %:label10, %86
	sti	 r1, %:label10, %91
	sti	 r1, %:label10, %96
	sti	 r1, %:label10, %101
	sti	 r1, %:label10, %106
	sti	 r1, %:label10, %111
	sti	 r1, %:label10, %116
	ld	 %48, r14
	ld	 %4, r4
	ld	 %48, r6
	ld	 %48, r13
	ld	 %108, r8
	ld	 %330, r9
	add	 r8, r9, r8
	ld	 %92, r12
	sub	 r12, r8, r12

label01:
	live	 %42
	fork	 %:label11

label02:
	live	 %42
	fork	 %:label04

label03:
	live	 %42
	fork	 %:label06
	ld	 %0, r15
	zjmp	 %:label08

label04:
	ld	 %0, r2

label05:
	live	 %42
	ldi	 %:label04, r2, r3
	sti	 r3, r8, r2
	add	 r2, r4, r2
	xor	 r13, r2, r7
	zjmp	 %415
	ld	 %0, r15
	zjmp	 %:label05

label06:
	ld	 %0, r10

label07:
	live	 %42
	ldi	 %:label06, r10, r11
	sti	 r11, r12, r10
	add	 r10, r4, r10
	xor	 r6, r10, r7
	zjmp	 %:label00
	ld	 %0, r15
	zjmp	 %:label07

label08:
	live	 %42
	fork	 %:label04

label09:
	live	 %42
	fork	 %:label06
	ld	 %0, r15
	zjmp	 %:label08

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
	live	 %42
	fork	 %:label10
	ld	 %0, r15
	zjmp	 %:label11
