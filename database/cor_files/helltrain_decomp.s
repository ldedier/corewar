.name "helltrain"
.comment "choo-choo, motherf*****s !"

	sti	 r1, %:label05, %1
	sti	 r1, %:label06, %1
	sti	 r1, %:label07, %1

label00:
	sti	 r1, %:label04, %1
	sti	 r1, %:label09, %1
	sti	 r1, %:label09, %9
	sti	 r1, %:label09, %17

label01:
	sti	 r1, %:label11, %1
	sti	 r1, %:label10, %2
	sti	 r1, %:label13, %1
	sti	 r1, %:label13, %9

label02:
	sti	 r1, %:label12, %1
	ld	 %0, r16
	fork	 %:label07

label03:
	ld	 %0, r2
	ld	 %0, r16

label04:
	live	 %4902343
	st	 r2, -24
	st	 r2, -33
	st	 r2, -42
	st	 r2, :label02
	st	 r2, -60
	st	 r2, -69
	st	 r2, -78
	st	 r2, -87
	st	 r2, -96
	st	 r2, -105
	st	 r2, :label01
	st	 r2, -123
	st	 r2, -132
	st	 r2, -141
	st	 r2, -150
	st	 r2, -159
	st	 r2, -168
	st	 r2, :label00
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
	zjmp	 %:label04

label05:
	live	 %4239423
	fork	 %:label05
	ld	 %0, r16

label06:
	live	 %3442302
	zjmp	 %:label06

label07:
	live	 %4320423
	zjmp	 %:label08

label08:
	fork	 %:label07

label09:
	live	 %4329034
	fork	 %:label13
	live	 %3401123
	fork	 %:label12
	live	 %4590543
	fork	 %:label14

label10:
	ld	 %0, r2
	ld	 %251883523, r3
	ld	 %0, r16

label11:
	live	 %4930423
	ld	 %0, r16
	zjmp	 %:label15

label12:
	live	 %4342342
	fork	 %:label03
	ld	 %251883523, r2
	ld	 %386101251, r3
	ld	 %0, r16
	ld	 %0, r16
	zjmp	 %:label15

label13:
	live	 %4239013
	fork	 %:label09
	live	 %4093282
	fork	 %:label05
	ld	 %-65280, r2
	ld	 %436432899, r3
	ld	 %0, r16
	ld	 %0, r16
	ld	 %0, r16
	zjmp	 %:label15

label14:
	ld	 %57672192, r2
	ld	 %318992387, r3
	ld	 %0, r16
	zjmp	 %:label15

label15:
	st	 r2, 15
	st	 r3, -1
	live	 %0
