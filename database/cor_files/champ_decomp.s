.name "lazer"
.comment "Mundo dit beaucoup son nom pour pas l'oublier, pck c deja arriver!"

	sti	 r1, %:label03, %1

label00:
	sti	 r1, %:label07, %1
	sti	 r1, %:label06, %1
	sti	 r1, %:label08, %1
	sti	 r1, %:label05, %1

label01:
	and	 r1, %0, r1

label02:
	ld	 %100, r4
	fork	 %:label06
	zjmp	 %:label07

label03:
	live	 %1566
	fork	 %:label05
	lfork	 %362
	zjmp	 %:label03

label04:
	ld	 %0, r8
	ld	 %5, r15

label05:
	live	 %2
	ldi	 %:label04, r8, r16
	sti	 r16, %394, r8
	add	 r15, r8, r8
	sti	 r16, %383, r8
	live	 %3
	xor	 r8, r3, r9
	zjmp	 %:label04
	ld	 %0, r9
	zjmp	 %:label05

label06:
	live	 %42
	ld	 %1111638594, r2
	st	 r2, -69
	st	 r2, -74
	st	 r2, -83
	st	 r2, :label04
	st	 r2, -101
	st	 r2, -109
	st	 r2, -115
	st	 r2, -123
	st	 r2, -132
	st	 r2, -141
	st	 r2, -150
	st	 r2, :label02
	st	 r2, -168
	st	 r2, :label01
	st	 r2, -186
	st	 r2, -195
	st	 r2, -204
	st	 r2, -213
	st	 r2, -222
	st	 r2, -231
	st	 r2, :label00
	st	 r2, -249
	st	 r2, -258
	st	 r2, -267
	st	 r2, -276
	st	 r2, -285
	st	 r2, -294
	st	 r2, -303
	st	 r2, -312
	st	 r2, -321
	st	 r2, -330
	st	 r2, -339
	st	 r2, -348
	st	 r2, -357
	st	 r2, -366
	st	 r2, -375
	st	 r2, -384
	st	 r2, -393
	st	 r2, -402
	st	 r2, -411
	st	 r2, -420
	st	 r2, -429
	st	 r2, -438
	st	 r2, -447
	st	 r2, -456
	st	 r2, -465
	st	 r2, -474
	st	 r2, -483
	st	 r2, -492
	st	 r2, -501
	st	 r2, -510
	zjmp	 %:label06
	ld	 %4, r8
	ld	 %0, r4
	ld	 %1111638594, r6

label07:
	live	 %99
	sti	 r6, 58, r4
	add	 r4, r8, r4
	sti	 r6, 47, r4
	add	 r4, r8, r4
	fork	 %:label07
	zjmp	 %:label07

label08:
	live	 %4242
	add	 r4, r8, r4
	sti	 r6, r4, %20
	add	 r4, r8, r4
	sti	 r6, r4, %9
	zjmp	 %:label08
