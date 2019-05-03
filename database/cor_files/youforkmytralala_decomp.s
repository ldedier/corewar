.name "Oh, You Fork my TRALALA ..."
.comment "HMMMM, my ding-ding-dong !!"

	st	 r1, 6
	st	 r1, r3
	live	 %42
	fork	 %:label00
	zjmp	 %:label02

label00:
	live	 %42
	st	 r15, -50
	st	 r15, -64
	st	 r15, -78
	st	 r15, -92
	st	 r15, -106
	st	 r15, -120
	st	 r15, -134
	st	 r15, -148
	st	 r15, -162
	st	 r15, -176
	st	 r15, -190
	st	 r15, -204
	st	 r15, -218
	st	 r15, -232
	st	 r15, -246
	st	 r15, -260
	st	 r15, -274
	st	 r15, -288
	st	 r15, -302
	st	 r15, -318

label01:
	st	 r15, -332
	st	 r15, -346
	st	 r15, -360
	st	 r15, -374
	st	 r15, -388
	st	 r15, -402
	st	 r15, -416
	st	 r15, -430
	st	 r15, -444
	st	 r15, -458
	st	 r15, -472
	st	 r15, -486
	st	 r15, -500
	st	 r16, 1
	live	 %42
	fork	 %:label00
	zjmp	 %:label00
	live	 %898
	fork	 %:label03
	live	 %1892
	fork	 %:label03
	live	 %4024
	fork	 %:label03
	live	 %232
	fork	 %:label03

label02:
	st	 r1, 6
	live	 %5
	fork	 %:label02
	zjmp	 %9

label03:
	st	 r1, 6
	live	 %42
	fork	 %:label03
	zjmp	 %1

label04:
	st	 r1, 6
	live	 %42
	fork	 %:label04
	zjmp	 %2

label05:
	st	 r1, 6
	live	 %7
	fork	 %:label05
	zjmp	 %:label06

label06:
	st	 r1, 6
	live	 %1
	fork	 %:label06
	zjmp	 %4

label07:
	live	 %512
	st	 r14, 1
	st	 r14, :label01
	st	 r14, -406
	st	 r14, -609
	st	 r14, -803
	st	 r14, -1006
	st	 r14, -1209
	st	 r14, -1403
	st	 r14, -1606
	st	 r14, -1809
	st	 r14, -2003
	st	 r14, -2206
	st	 r14, -2409
	st	 r14, -2603
	st	 r14, -2806
	st	 r14, -3009
	st	 r14, -3203
	st	 r14, -3406
	st	 r14, -3609
	st	 r14, -3803
	st	 r14, -4006
	st	 r14, -4209
	st	 r14, -4403
	st	 r14, -4606
	st	 r14, -4809
	st	 r14, -5003
	st	 r14, -5206
	st	 r14, -5409
	st	 r14, -5603
	st	 r14, -5806
	st	 r14, -6009
	st	 r14, -6203
	st	 r14, -6406
	st	 r14, -6609
	st	 r14, -6803
	st	 r14, -7006
	st	 r14, -7209
	st	 r14, -7403
	st	 r14, -7606
	st	 r14, -7809
	st	 r14, -8003
	st	 r1, 6
	live	 %1
	zjmp	 %:label07
	fork	 %:label07
