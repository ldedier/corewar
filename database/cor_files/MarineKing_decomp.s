.name "MKP"
.comment "SaR ez Gg"

	sti	 r1, %:label09, %1

label00:
	st	 r1, 6
	live	 %433
	ld	 %1, r2
	live	 %45223
	ld	 %1, r3
	live	 %13123
	sti	 r1, %:label07, %1
	ld	 %0, r15

label01:
	live	 %45223
	fork	 %:label04

label02:
	ld	 %0, r15
	add	 r2, r3, r2

label03:
	zjmp	 %:label07

label04:
	live	 %651

label05:
	fork	 %:label06
	ld	 %0, r15
	ld	 %0, r15
	ld	 %0, r15
	zjmp	 %:label04

label06:
	live	 %9814
	fork	 %:label01

label07:
	live	 %4902343
	st	 r2, -24
	st	 r2, -33
	st	 r2, -42
	st	 r2, -51
	st	 r2, :label05
	st	 r2, -69
	st	 r2, :label03
	st	 r2, -87
	st	 r2, -96
	st	 r2, :label02
	st	 r2, -114
	st	 r2, :label01
	st	 r2, -132
	st	 r2, -141
	st	 r2, -150
	st	 r2, -159
	st	 r2, -168
	st	 r2, -177
	st	 r2, -186
	st	 r2, -195
	st	 r2, -204
	st	 r2, -213
	st	 r2, -222
	st	 r2, :label00
	st	 r2, -240
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
	zjmp	 %:label07

label08:
	live	 %651264
	add	 r2, r3, r2
	xor	 r2, %15, r4
	zjmp	 %:label08

label09:
	live	 %1
	zjmp	 %:label09

label10:
	live	 %6514
	zjmp	 %:label08
	ld	 %0, r4
	zjmp	 %:label10
	live	 %9751364
	ld	 %0, r4
