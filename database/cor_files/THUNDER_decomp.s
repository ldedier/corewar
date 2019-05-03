.name "thunder"
.comment "you've been thunderstruck..."

	sti	 r1, %:label03, %1
	sti	 r1, %:label02, %1
	sti	 r1, %:label04, %1

label00:
	sti	 r1, %:label01, %1
	ld	 %0, r16
	fork	 %:label03

label01:
	live	 %42
	ld	 %0, r2
	ld	 %0, r16
	fork	 %:label04

label02:
	live	 %42
	st	 r2, -24
	st	 r2, -33
	st	 r2, -42
	st	 r2, -51
	st	 r2, -60
	st	 r2, :label00
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
	zjmp	 %:label02

label03:
	live	 %42
	zjmp	 %:label03

label04:
	live	 %42
	st	 r2, 24
	st	 r2, 33
	st	 r2, 42
	st	 r2, 51
	st	 r2, :label05
	st	 r2, 69
	st	 r2, 78
	st	 r2, 87
	st	 r2, 96
	st	 r2, :label06
	st	 r2, 114
	st	 r2, 123
	st	 r2, 132
	st	 r2, 141
	st	 r2, :label07
	st	 r2, 159

label05:
	st	 r2, 168
	st	 r2, 177
	st	 r2, 186
	st	 r2, 195
	st	 r2, 204
	st	 r2, 213
	st	 r2, 222
	st	 r2, 231
	st	 r2, 240
	st	 r2, 249
	st	 r2, 258
	st	 r2, 267
	st	 r2, 276
	st	 r2, 285

label06:
	st	 r2, 294
	st	 r2, 303
	st	 r2, 312
	st	 r2, 321
	st	 r2, 330
	st	 r2, 339
	st	 r2, 348
	st	 r2, 357
	st	 r2, 366
	st	 r2, 375
	st	 r2, 384
	st	 r2, 393
	st	 r2, 402
	st	 r2, 411

label07:
	st	 r2, 420
	st	 r2, 429
	st	 r2, 438
	st	 r2, 447
	st	 r2, 456
	st	 r2, 465
	st	 r2, 474
	st	 r2, 483
	st	 r2, 492
	st	 r2, 501
	st	 r2, 510
	zjmp	 %:label04
