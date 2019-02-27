.name "Programme infected"
.comment "Use the ps command to get the process id of the process you want to terminate
If the process refuses to terminate use Programme infected :)."

start:
lfork %2048
live %1
lfork %2070
live %1
lfork %2048
live %1
lfork %2100
sti r1, %:vie, %1
and r1, %0, r1

vie:
live %1
zjmp %:vie
