.name "zdoh"
.comment "w8 for da next one"

	sti	 r3, -1, %1
	and	 r3, %0, r3

label00:
	fork	 %:label01
	ld	 0, r4
	st	 r4, -6
	zjmp	 %:label00

label01:
	live	 %0
	live	 %42
	fork	 %:label09

label02:
	fork	 %:label09
	fork	 %:label09
	fork	 %:label09
	fork	 %:label09
	fork	 %:label09

label03:
	fork	 %:label09
	fork	 %:label09
	fork	 %:label09
	fork	 %:label09
	fork	 %:label01

label04:
	fork	 %:label01
	fork	 %:label09
	fork	 %:label01
	fork	 %:label08
	fork	 %:label09

label05:
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10

label06:
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10
	fork	 %:label10

label07:
	fork	 %:label10
	fork	 %:label10

label08:
	fork	 %:label01

label09:
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	fork	 %:label10
	fork	 %:label09

label10:
	live	 %42
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -500
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label02
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label03
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label04
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label05
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label06
	st	 r8, -400
	st	 r8, -400
	st	 r8, :label07
	st	 r8, -400
	zjmp	 %:label10
