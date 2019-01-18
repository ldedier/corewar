.name			"ah"
.comment		"Hmmm"

ld %0, r3
zjmp %:here

there:	live %42;

here:	sti r1,%:there,%1
		zjmp %:there
 
