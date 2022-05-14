___
Instruction : clr \
Description : Clears the screen \
Operands : 
```
clr
```
___
Instruction : ret \
Description : Returns from routine \
Operands : 
```
ret
```
___
Instruction : jmp \
Description : Jump to instruction \
Operands : 
```
jmp	instruction_label
jmp	literal
```
___
Instruction : call \
Description : Calls a routine \
Operands : 
```
call	instruction_label
call	literal
```
___
Instruction : se \
Description : Skips an instruction if operands are equal \
Operands : 
```
se	vx,	literal
se	vx,	vx
```
___
Instruction : sne \
Description : Skips an instruction if operands are not equal \
Operands : 
```
sne	vx,	literal
sne	vx,	vx
```
___
Instruction : mov \
Description : Moves the second operand's value into the first \
Operands : 
```
mov	vx,	literal
mov	vx,	vx
mov	vx,	dly
mov	ptr,	instruction_label
mov	ptr,	literal
mov	snd,	vx
mov	dly,	vx
```
___
Instruction : add \
Description : Adds the second operand's value to the first \
Operands : 
```
add	vx,	literal
add	vx,	vx
add	ptr,	vx
```
___
Instruction : or \
Description : Bitwise OR between operands \
Operands : 
```
or	vx,	vx
```
___
Instruction : and \
Description : Bitwise AND between operands \
Operands : 
```
and	vx,	vx
```
___
Instruction : xor \
Description : Bitwise XOR betwen operands \
Operands : 
```
xor	vx,	vx
```
___
Instruction : sub \
Description : Subtracs the second operand's value from the first \
Operands : 
```
sub	vx,	vx
```
___
Instruction : shr \
Description : Bitshifts operand right by 1 \
Operands : 
```
shr	vx
```
___
Instruction : shl \
Description : Bitshifts operand left by 1 \
Operands : 
```
shl	vx
```
___
Instruction : subo \
Description : Subtracts the first operand from the second and puts it in the first operand \
Operands : 
```
subo	vx,	vx
```
___
Instruction : spt \
Description : Sets the ptr to the sprite in the operand \
Operands : 
```
spt	vx
```
___
Instruction : bcd \
Description : Sets the binary coded decimal in the first operand at the current ptr location \
Operands : 
```
bcd	vx
```
___
Instruction : dump \
Description : Dumps the registers up to the first operand at the current ptr \
Operands : 
```
dump	vx
```
___
Instruction : load \
Description : Loads the registers up to the first operand at the current ptr \
Operands : 
```
load	vx
```
___
Instruction : draw \
Description : Draws a sprite from ptr at the first operand for x and the second operand for y with a sprite height of the third operand \
Operands : 
```
draw	vx,	vx,	literal
```
___
Instruction : rnd \
Description : Sets the first operand to a random number between 0-255 bitwise and with second operand \
Operands : 
```
rnd	vx,	literal
```
___
Instruction : mjmp \
Description : Sets the ptr to the first operand + the current value of register 0 \
Operands : 
```
mjmp	instruction_label
mjmp	literal
```
___
Instruction : sk \
Description : Skips the next instruction if the key in the first operand is held \
Operands : 
```
sk	vx
```
___
Instruction : snk \
Description : Skips the next instruction if the key in the first operand is not held \
Operands : 
```
snk	vx
```
___
Instruction : wtk \
Description : Waits for a key press and then puts the result in the first operand \
Operands : 
```
wtk	vx
```
