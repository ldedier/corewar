.name "lld"
.comment "lol"

before:
before:

middle:
lld %-2147483648, r1
lld %2147483648, r1
lld %2147483647, r1
lld %214748364732488, r1
lld %1, r1
lld %-1, r1
lld %10, r1
lld %-10, r1
lld %-500, r1
lld %500, r1
lld %:before, r1
lld %:middle, r1
lld %:after, r1
lld -2147483648, r1
lld 2147483648, r1
lld 2147483647, r1
lld 214748364732488, r1
lld 1, r1
lld -1, r1
lld 10, r1
lld -10, r1
lld -500, r1
lld 500, r1
lld :before, r1
lld :middle, r1
lld :after, r1

after:

middle:
lld %-2147483648, r7
lld %2147483648, r7
lld %2147483647, r7
lld %214748364732488, r7
lld %1, r7
lld %-1, r7
lld %10, r7
lld %-10, r7
lld %-500, r7
lld %500, r7
lld %:before, r7
lld %:middle, r7
lld %:after, r7
lld -2147483648, r7
lld 2147483648, r7
lld 2147483647, r7
lld 214748364732488, r7
lld 1, r7
lld -1, r7
lld 10, r7
lld -10, r7
lld -500, r7
lld 500, r7
lld :before, r7
lld :middle, r7
lld :after, r7

after:

middle:
lld %-2147483648, r16
lld %2147483648, r16
lld %2147483647, r16
lld %214748364732488, r16
lld %1, r16
lld %-1, r16
lld %10, r16
lld %-10, r16
lld %-500, r16
lld %500, r16
lld %:before, r16
lld %:middle, r16
lld %:after, r16
lld -2147483648, r16
lld 2147483648, r16
lld 2147483647, r16
lld 214748364732488, r16
lld 1, r16
lld -1, r16
lld 10, r16
lld -10, r16
lld -500, r16
lld 500, r16
lld :before, r16
lld :middle, r16
lld :after, r16

after:
