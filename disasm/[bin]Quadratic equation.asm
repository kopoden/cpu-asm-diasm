in
pop reg1
in
pop reg2
in
pop reg3
push reg1
push 0
je 76
push reg2
push reg2
mul
push reg3
push reg1
push -4
mul
mul
add
pop reg4
push reg4
push 0
jb 104
push reg4
push 0
je 105
push reg4
sqrt
pop reg4
push -1
push reg2
mul
push reg4
add
push 2
push reg1
mul
div
out
push reg2
push reg4
add
push -2
push reg1
mul
div
out
end
push reg2
push 0
je 92
push reg3
push reg2
div
push -1
mul
out
end
push reg3
push 0
jne 104
push 0
push 0
out
out
end
push reg2
push reg1
push -2
mul
div
out
