.name "mandragore"
.comment "you can see me, you can't anymore, you can, you can't !"


label00:
	sti	 r1, %:label01, %1
	sti	 r1, %:label02, %1
	fork	 %:label02
	sti	 r1, %:label03, %1
	ld	 %0, r2

label01:
	live	 %569092
	st	 r2, -24
	st	 r2, -33
	st	 r2, -42
	st	 r2, :label00
	st	 r2, -60
	st	 r2, -69
	st	 r2, -78
	st	 r2, -87
	st	 r2, -96
	st	 r2, -105
	st	 r2, -114
	st	 r2, -123
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
	st	 r2, -231
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
	ld	 %0, r2
	zjmp	 %:label01

label02:
	live	 %235894
	fork	 %:label02
	zjmp	 %:label05

label03:
	live	 %265924
	fork	 %:label02
	zjmp	 %:label02
	sti	 r1, %:label05, %1
	ld	 %1, r3
	ld	 %512, r5
	ld	 %1024, r7

label04:
	add	 r6, r3, r6
	zjmp	 %:label03

label05:
	live	 %568724
	add	 r6, r5, r7
	sti	 r7, r5, r7
	fork	 %:label02
	zjmp	 %:label04
