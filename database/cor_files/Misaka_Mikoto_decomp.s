.name "Misaka Mikoto"
.comment "Misaka Mikoto (御坂 美琴 Misaka Mikoto) (born May 2) is a main heroine in Toaru Majutsu no Index and the main protagonist of Toaru Kagaku no Railgun. Introduced in the first volume of the light novels, her role in the story was later expanded in the third volume as well as the release of the Toaru Kagaku no Railgun manga, making her the main heroine of the science side and the second main heroine of the series.

	She is the third ranked Level 5 esper in Academy City, and is nicknamed the Railgun due to her signature move. Kamijou Touma coined the nickname Biri-Biri (ビリビリ?) (a Japanese onomatopoeia imitating the sound of electricity) for her and whenever the two meet he usually calls her that, even after his amnesia"


label00:
	sti	 r1, %:label29, %1
	sti	 r1, %:label03, %1
	sti	 r1, %:label04, %1
	sti	 r1, %:label07, %1
	sti	 r1, %:label10, %1
	st	 r2, :label00
	fork	 %:label01
	add	 r3, r3, r3
	zjmp	 %:label31
	zjmp	 %:label29
	zjmp	 %:label29
	zjmp	 %:label29
	zjmp	 %:label29
	zjmp	 %:label29
	zjmp	 %:label29

label01:
	live	 %404
	add	 r3, r3, r3
	fork	 %:label02
	zjmp	 %:label03

label02:
	zjmp	 %:label04

label03:
	live	 %404
	fork	 %:label05
	zjmp	 %:label07

label04:
	live	 %404
	fork	 %:label06
	zjmp	 %:label08

label05:
	zjmp	 %:label09

label06:
	zjmp	 %:label10

label07:
	live	 %404
	fork	 %:label11
	zjmp	 %:label25

label08:
	live	 %404
	fork	 %:label12
	zjmp	 %:label15

label09:
	live	 %404
	fork	 %:label14
	zjmp	 %:label21

label10:
	live	 %404
	fork	 %:label13
	zjmp	 %:label19

label11:
	zjmp	 %:label26

label12:
	zjmp	 %:label17

label13:
	zjmp	 %:label23

label14:
	zjmp	 %:label28

label15:
	ld	 %-498, r9

label16:
	ldi	 %:label16, %222, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label17:
	ld	 %-504, r9

label18:
	ldi	 %:label18, %200, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label19:
	ld	 %508, r9

label20:
	ldi	 %:label20, %181, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label21:
	ld	 %516, r9

label22:
	ldi	 %:label22, %159, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label23:
	ld	 %512, r9

label24:
	ldi	 %:label24, %137, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label25:
	ld	 %19, r9
	ldi	 %8, %59, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label26:
	ld	 %11, r9

label27:
	ldi	 %:label27, %37, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label28:
	ld	 %15, r9
	ldi	 %4, %15, r8
	add	 r3, r3, r3
	zjmp	 %:label29

label29:
	live	 %777
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	sti	 r8, %:label29, r9
	lfork	 %-50

label30:
	zjmp	 %:label30
	live	 %404

label31:
	ldi	 %:label31, %-5, r3
	ldi	 %:label32, %0, r2

label32:
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	st	 r2, 256
	live	 %404
	st	 r3, 256
