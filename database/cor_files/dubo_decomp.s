.name "dubo"
.comment "Tu veux du pain"


label00:
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	live	 %1
	zjmp	 %:label00

label01:
	live	 %1
	live	 %1
	live	 %1
	live	 %3
	live	 %2
	live	 %2
	zjmp	 %:label01
