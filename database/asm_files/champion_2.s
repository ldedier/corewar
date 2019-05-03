.name "Kill Process"
.comment "en test"


begin:
lfork %2048

init:
live    %1
ld      %57672705, r4
fork    %:attack
live    %1
ld %0, r2
fork    %:save

attack:
lfork %2048
st      r4, 300
st      r4, 300
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
st      r4, 300
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
st      r4, 300
st      r4, 300
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
st      r4, 300
st      r4, 300
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
live %1
st      r4, 300
zjmp %:attack
sti r1, %:save, %1

save:
live %1
zjmp %:save
