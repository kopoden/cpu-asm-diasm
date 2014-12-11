in
pop reg1 //A
in
pop reg2 //B
in
pop reg3 //C
push reg1
push 0
je 1
push reg2
push reg2
mul
push reg3
push reg1
push -4
mul
mul
add
pop reg4 //Discriminant
push reg4
push 0
jb 3 // D < 0
push reg4
push 0
je 4 // D = 0
push reg4 // D > 0
sqrt
pop reg4
push -1 // First root +
push reg2
mul
push reg4
add
push 2
push reg1
mul
div
out
push reg2 // Second root -
push reg4
add
push -2
push reg1
mul
div
out
end

:1 //Linear
push reg2
push 0
je 2
push reg3
push reg2
div
push -1
mul
out
end

:2 //Infinite
push reg3
push 0
jne 3 //None
push 0
push 0
out
out
:3
end

:4 //D = 0
push reg2
push reg1
push -2
mul
div
out
end