.name "Candy"
.comment ""

	st	 r1, r12

label00:
	ld	 %0, r14
	zjmp	 %:label05

label01:
	st	 r9, -256
	st	 r10, -256
	st	 r14, -9
	st	 r4, -21
	st	 r14, :label00
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256

label02:
	st	 r4, -256
	st	 r4, -256
	st	 r9, -256
	st	 r10, -256
	st	 r14, -9
	st	 r4, -21
	st	 r14, :label02
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256

label03:
	st	 r4, -256
	st	 r4, -256
	st	 r4, -256
	st	 r10, -256
	st	 r14, -9
	st	 r4, -21
	st	 r14, :label03
	ld	 %0, r15
	zjmp	 %:label01

label04:
	live	 %42
	fork	 %:label07
	ld	 %0, r16
	zjmp	 %:label05

label05:
	live	 %42
	ld	 %57672449, r3
	ld	 %57672959, r4
	ld	 %42991616, r9
	ld	 %235536380, r10
	ld	 %16777216, r11
	xor	 r12, r14, r15
	sti	 r15, %:label06, %1
	sti	 r15, %:label04, %1
	sti	 r15, %:label09, %1
	zjmp	 %:label06

label06:
	live	 %42
	fork	 %:label01
	fork	 %:label10
	ld	 %0, r15
	zjmp	 %:label04

label07:
	st	 r3, 256
	st	 r3, 256
	st	 r3, 256
	live	 %1
	st	 r3, 256
	st	 r3, 256
	st	 r3, 256
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, :label10
	st	 r3, :label11
	st	 r3, 256
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	st	 r3, 256
	st	 r3, 256
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	live	 %1
	st	 r3, 256
	zjmp	 %:label07

label08:
	live	 %42
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	st	 r9, 256
	zjmp	 %:label08

label09:
	live	 %1

label10:
	live	 %1

label11:
	fork	 %:label08
	st	 r4, 254
	zjmp	 %:label10
