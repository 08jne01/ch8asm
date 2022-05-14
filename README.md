---
INSTRUCTION: clr
DESCRIPTION: Clears the screen
OPERANDS: 
	clr
---
INSTRUCTION: ret
DESCRIPTION: Returns from routine
OPERANDS: 
	ret
---
INSTRUCTION: jmp
DESCRIPTION: Jump to instruction
OPERANDS: 
	jmp	instruction_label
	jmp	literal
---
INSTRUCTION: call
DESCRIPTION: Calls a routine
OPERANDS: 
	call	instruction_label
	call	literal
---
INSTRUCTION: se
DESCRIPTION: Skips an instruction if operands are equal
OPERANDS: 
	se	vx,	literal
	se	vx,	vx
---
INSTRUCTION: sne
DESCRIPTION: Skips an instruction if operands are not equal
OPERANDS: 
	sne	vx,	literal
	sne	vx,	vx
---
INSTRUCTION: mov
DESCRIPTION: Moves the second operand's value into the first
OPERANDS: 
	mov	vx,	literal
	mov	vx,	vx
	mov	vx,	dly
	mov	ptr,	instruction_label
	mov	ptr,	literal
	mov	snd,	vx
	mov	dly,	vx
---
INSTRUCTION: add
DESCRIPTION: Adds the second operand's value to the first
OPERANDS: 
	add	vx,	literal
	add	vx,	vx
	add	ptr,	vx
---
INSTRUCTION: or
DESCRIPTION: Bitwise OR between operands
OPERANDS: 
	or	vx,	vx
---
INSTRUCTION: and
DESCRIPTION: Bitwise AND between operands
OPERANDS: 
	and	vx,	vx
---
INSTRUCTION: xor
DESCRIPTION: Bitwise XOR betwen operands
OPERANDS: 
	xor	vx,	vx
---
INSTRUCTION: sub
DESCRIPTION: Subtracs the second operand's value from the first
OPERANDS: 
	sub	vx,	vx
---
INSTRUCTION: shr
DESCRIPTION: Bitshifts operand right by 1
OPERANDS: 
	shr	vx
---
INSTRUCTION: shl
DESCRIPTION: Bitshifts operand left by 1
OPERANDS: 
	shl	vx
---
INSTRUCTION: subo
DESCRIPTION: Subtracts the first operand from the second and puts it in the first operand
OPERANDS: 
	subo	vx,	vx
---
INSTRUCTION: spt
DESCRIPTION: Sets the ptr to the sprite in the operand
OPERANDS: 
	spt	vx
---
INSTRUCTION: bcd
DESCRIPTION: Sets the binary coded decimal in the first operand at the current ptr location
OPERANDS: 
	bcd	vx
---
INSTRUCTION: dump
DESCRIPTION: Dumps the registers up to the first operand at the current ptr
OPERANDS: 
	dump	vx
---
INSTRUCTION: load
DESCRIPTION: Loads the registers up to the first operand at the current ptr
OPERANDS: 
	load	vx
---
INSTRUCTION: draw
DESCRIPTION: Draws a sprite from ptr at the first operand for x and the second operand for y with a sprite height of the third operand
OPERANDS: 
	draw	vx,	vx,	literal
---
INSTRUCTION: rnd
DESCRIPTION: Sets the first operand to a random number between 0-255 bitwise and with second operand
OPERANDS: 
	rnd	vx,	literal
---
INSTRUCTION: mjmp
DESCRIPTION: Sets the ptr to the first operand + the current value of register 0
OPERANDS: 
	mjmp	instruction_label
	mjmp	literal
---
INSTRUCTION: sk
DESCRIPTION: Skips the next instruction if the key in the first operand is held
OPERANDS: 
	sk	vx
---
INSTRUCTION: snk
DESCRIPTION: Skips the next instruction if the key in the first operand is not held
OPERANDS: 
	snk	vx
---
INSTRUCTION: wtk
DESCRIPTION: Waits for a key press and then puts the result in the first operand
OPERANDS: 
	wtk	vx
