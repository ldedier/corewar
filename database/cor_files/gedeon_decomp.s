.name "Gédéon le Cochon"
.comment "Tout est bon dans Gédéon"

	sti	 r1, %:label02, %1
	sti	 r1, %:label03, %1

label00:
	sti	 r1, %:label03, %9
	sti	 r1, %:label03, %17
	sti	 r1, %:label03, %25
	sti	 r1, %:label04, %1

label01:
	sti	 r1, %:label05, %1
	sti	 r1, %:label06, %1
	ld	 %0, r1
	fork	 %:label03
	ld	 %0, r1

label02:
	live	 %1337
	st	 r1, -16
	st	 r1, -25
	st	 r1, -34
	st	 r1, -43
	st	 r1, -52
	st	 r1, :label01
	st	 r1, -70
	st	 r1, -79
	st	 r1, -88
	st	 r1, -97
	st	 r1, -106
	st	 r1, -115
	st	 r1, :label00
	st	 r1, -133
	st	 r1, -142
	st	 r1, -151
	st	 r1, -160
	st	 r1, -410
	st	 r1, -411
	st	 r1, -412
	st	 r1, -413
	st	 r1, -414
	st	 r1, -425
	st	 r1, -416
	st	 r1, -417
	st	 r1, -418
	st	 r1, -419
	ld	 %0, r1
	zjmp	 %:label02

label03:
	live	 %1337
	fork	 %:label02
	live	 %1337
	fork	 %:label06
	live	 %1337
	fork	 %:label04
	live	 %1337
	fork	 %:label03
	zjmp	 %:label03

label04:
	live	 %1337
	fork	 %:label04
	ld	 %0, r1

label05:
	live	 %1337
	zjmp	 %:label05

label06:
	live	 %1337
	st	 r1, 30
	st	 r1, 29
	st	 r1, 28
	st	 r1, 27
	ld	 %0, r1
	zjmp	 %:label06
