in
pop reg4
mov reg1 1
mov reg2 1
push 0
push reg4
jae 2
mov reg3 2
:4
push reg3
push reg4
jae 1
jmp 3
end
						
:1
push reg2
out
end
						
:2
push -1
out
end
						
:3
push reg1
push reg2
add
push reg2
pop reg1
pop reg2
push 1
push reg3
add
pop reg3
jmp 4
