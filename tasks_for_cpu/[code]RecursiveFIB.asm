in
pop reg4
mov reg1 0
mov reg2 1
mov reg3 2
push reg4
push 0
jb 1
push reg4
push 0
je 4
call 2
push reg2
out
end


:4
push reg1
out
end

:1
push -1
out
end


:2
push reg4
push reg3
jbe 3
push reg4
push -1
add
pop reg4
call 2
:3
push reg2
push reg2
push reg1
add
pop reg2
pop reg1
ret
