.name "prout"
.comment "ca pue"

live %255
ld %255, r16
ld 255, r16
st r16, r2
st r2, 255
add r1, r2, r3
sub r1, r2, r4
and r1, r2, r5
and r1, %255, r6
and r1, -6, r7
and %256, r2, r7
and %256, %255, r7
and %256, -6, r7
and -15, r7, r7
and -200, %256, r7
and -200, -200, r8
or r1, r2, r5
or r1, %255, r6
or r1, -6, r7
or %256, r2, r7
or %256, %255, r7
or %256, -6, r7
or -15, r7, r7
or -200, %256, r7
or -200, -200, r8
xor r1, r2, r5
xor r1, %255, r6
xor r1, -6, r7
xor %256, r2, r7
xor %256, %255, r7
xor %256, -6, r7
xor -15, r7, r7
xor -200, %256, r7
xor -200, -200, r8
ld 0, r2
zjmp %3
zjmp %1
ldi r1, r2, r4
ldi r1, %400, r4
ldi %400, r2, r4
ldi %400, %1, r4
ldi -1, r4, r4
ldi -1, %400, r4
sti r1, r2, r4
sti r1, r2, %1
sti r1, %2, r1
sti r1, %2, %1
sti r1, -20, r4
sti r1, -20, %1
fork %120
lld %120, r4
lld -10, r4
lldi r1, r2, r4
lldi r1, %400, r4
lldi %400, r2, r4
lldi %400, %1, r4
lldi -1, r4, r4
lldi -1, %400, r4
lfork %12000
ld %42, r1
ld %42, r2
ld %42, r16
aff r1
aff r2
aff r16
