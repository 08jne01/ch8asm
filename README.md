___
| INSTRUCTION | clr |
| DESCRIPTION | Clears the screen |
| OPERANDS | ```	clr
```___
| INSTRUCTION | ret |
| DESCRIPTION | Returns from routine |
| OPERANDS | ```	ret
```___
| INSTRUCTION | jmp |
| DESCRIPTION | Jump to instruction |
| OPERANDS | ```	jmp	instruction_label
	jmp	literal
```___
| INSTRUCTION | call |
| DESCRIPTION | Calls a routine |
| OPERANDS | ```	call	instruction_label
	call	literal
```___
| INSTRUCTION | se |
| DESCRIPTION | Skips an instruction if operands are equal |
| OPERANDS | ```	se	vx,	literal
	se	vx,	vx
```___
| INSTRUCTION | sne |
| DESCRIPTION | Skips an instruction if operands are not equal |
| OPERANDS | ```	sne	vx,	literal
	sne	vx,	vx
```___
| INSTRUCTION | mov |
| DESCRIPTION | Moves the second operand's value into the first |
| OPERANDS | ```	mov	vx,	literal
	mov	vx,	vx
	mov	vx,	dly
	mov	ptr,	instruction_label
	mov	ptr,	literal
	mov	snd,	vx
	mov	dly,	vx
```___
| INSTRUCTION | add |
| DESCRIPTION | Adds the second operand's value to the first |
| OPERANDS | ```	add	vx,	literal
	add	vx,	vx
	add	ptr,	vx
```___
| INSTRUCTION | or |
| DESCRIPTION | Bitwise OR between operands |
| OPERANDS | ```	or	vx,	vx
```___
| INSTRUCTION | and |
| DESCRIPTION | Bitwise AND between operands |
| OPERANDS | ```	and	vx,	vx
```___
| INSTRUCTION | xor |
| DESCRIPTION | Bitwise XOR betwen operands |
| OPERANDS | ```	xor	vx,	vx
```___
| INSTRUCTION | sub |
| DESCRIPTION | Subtracs the second operand's value from the first |
| OPERANDS | ```	sub	vx,	vx
```___
| INSTRUCTION | shr |
| DESCRIPTION | Bitshifts operand right by 1 |
| OPERANDS | ```	shr	vx
```___
| INSTRUCTION | shl |
| DESCRIPTION | Bitshifts operand left by 1 |
| OPERANDS | ```	shl	vx
```___
| INSTRUCTION | subo |
| DESCRIPTION | Subtracts the first operand from the second and puts it in the first operand |
| OPERANDS | ```	subo	vx,	vx
```___
| INSTRUCTION | spt |
| DESCRIPTION | Sets the ptr to the sprite in the operand |
| OPERANDS | ```	spt	vx
```___
| INSTRUCTION | bcd |
| DESCRIPTION | Sets the binary coded decimal in the first operand at the current ptr location |
| OPERANDS | ```	bcd	vx
```___
| INSTRUCTION | dump |
| DESCRIPTION | Dumps the registers up to the first operand at the current ptr |
| OPERANDS | ```	dump	vx
```___
| INSTRUCTION | load |
| DESCRIPTION | Loads the registers up to the first operand at the current ptr |
| OPERANDS | ```	load	vx
```___
| INSTRUCTION | draw |
| DESCRIPTION | Draws a sprite from ptr at the first operand for x and the second operand for y with a sprite height of the third operand |
| OPERANDS | ```	draw	vx,	vx,	literal
```___
| INSTRUCTION | rnd |
| DESCRIPTION | Sets the first operand to a random number between 0-255 bitwise and with second operand |
| OPERANDS | ```	rnd	vx,	literal
```___
| INSTRUCTION | mjmp |
| DESCRIPTION | Sets the ptr to the first operand + the current value of register 0 |
| OPERANDS | ```	mjmp	instruction_label
	mjmp	literal
```___
| INSTRUCTION | sk |
| DESCRIPTION | Skips the next instruction if the key in the first operand is held |
| OPERANDS | ```	sk	vx
```___
| INSTRUCTION | snk |
| DESCRIPTION | Skips the next instruction if the key in the first operand is not held |
| OPERANDS | ```	snk	vx
```___
| INSTRUCTION | wtk |
| DESCRIPTION | Waits for a key press and then puts the result in the first operand |
| OPERANDS | ```	wtk	vx
```