.name "Kill Process"
.comment "en test"


begin:
lfork %2048
zjmp    %:init #--> base

live:
live    %1
zjmp    %:init

init:
ld        %57672705, r4
fork  %:attack
zjmp    %:live1

live1:
live    %42
ld %0, r2
fork    %:save
zjmp    %:live


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
zjmp %:live1


sti r1, %:save, %1

save:
live %1
zjmp %:save
