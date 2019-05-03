.name "Underscore"
.comment "__UNDERSCORE_S__"


label00:
	ld	 %0, r2
	zjmp	 %:label18
	zjmp	 %-511

label01:
	live	 %-42
	sti	 r10, r11, r13
	add	 r12, r13, r13
	xor	 r13, %-255, r14
	zjmp	 %:label02
	ld	 %0, r14
	zjmp	 %:label01

label02:
	ld	 %0, r13
	zjmp	 %:label01

label03:
	live	 %-42
	ld	 %-128, r6
	fork	 %:label04
	ld	 %190056198, r7
	ld	 %0, r5
	ld	 %0, r16
	zjmp	 %:label07

label04:
	ld	 %84541307, r7
	ld	 %4, r5
	ld	 %190056198, r16

label05:
	st	 r16, -490

label06:
	st	 r7, -491

label07:
	ld	 %0, r2
	zjmp	 %-511
	lldi	 %42, %42, r16

label08:
	live	 %-42
	sti	 r1, %:label01, %1
	ld	 %57672959, r10
	ld	 %-30, r11
	ld	 %-5, r12
	st	 r1, 6

label09:
	live	 %-42
	fork	 %:label01
	ld	 %-165, r13
	ld	 %0, r2
	zjmp	 %:label09

label10:
	sti	 r1, %:label12, %1
	sti	 r1, %:label14, %1
	fork	 %:label08
	st	 r1, 6
	live	 %-42
	or	 r1, r1, r7
	ld	 %1880161814, r9
	ld	 %1879571989, r10
	ld	 %34209281, r11

label11:
	fork	 %:label14

label12:
	live	 %-42
	fork	 %:label13
	ld	 %0, r2
	zjmp	 %:label17

label13:
	ld	 %191104768, r7
	ld	 %5, r6
	ld	 %0, r2
	zjmp	 %:label16

label14:
	live	 %-42
	fork	 %:label15
	ld	 %101056768, r7
	ld	 %9, r6
	ld	 %0, r2
	zjmp	 %:label16

label15:
	ld	 %0, r2
	ld	 %12, r6
	ld	 %0, r2
	zjmp	 %:label16

label16:
	st	 r1, 6
	live	 %-42
	sti	 r7, r6, %317
	ld	 %0, r2
	zjmp	 %309
	sti	 r16, %:label20, %1
	fork	 %:label19
	ld	 %24, r16
	sti	 r16, %:label20, %1
	st	 r1, 6
	live	 %-42
	ld	 %0, r2
	zjmp	 %511

label17:
	ld	 %16, r12
	add	 r12, r9, r9
	add	 r12, r10, r10
	add	 r12, r11, r11
	st	 r1, 6
	live	 %-42
	ld	 %0, r2
	sti	 r1, %:label03, %1
	sti	 r9, %:label05, %1
	sti	 r10, %:label06, %1
	sti	 r11, %:label07, %6
	fork	 %:label03
	zjmp	 %:label11

label18:
	ld	 %16777216, r16
	sti	 r16, %:label00, %6
	st	 r1, 117
	sti	 r1, %:label21, %1
	ld	 %507, r4
	ld	 %507, r6
	st	 r1, 6
	live	 %-42

label19:
	ld	 %190055170, r8
	ld	 %67699190, r9
	st	 r8, 511
	st	 r9, 510

label20:
	ld	 %24, r8
	fork	 %:label10
	fork	 %:label22

label21:
	live	 %-1
	ld	 %0, r2
	ld	 %190055682, r3
	ld	 %190056194, r5
	ld	 %190056194, r7
	ld	 %0, r16
	zjmp	 %448

label22:
	live	 %0
	ld	 %4, r2
	ld	 %101253622, r3
	ld	 %134807571, r5
	ld	 %134807571, r7
	ld	 %0, r16
	zjmp	 %405
