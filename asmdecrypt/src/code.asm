.CODE


decrypt_gobjects PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov r8d,ecx
	mov r9,rcx
	movzx ecx,cx
	shr r9,20h
	shr r8d,10h
	xor ecx,r8d
	movzx eax,r8w
	rol ax,08h
	movzx edx,ax
	shl edx,10h
	or edx,ecx
	add edx,33D3075Dh
	mov ecx,edx
	movzx eax,dx
	shr ecx,10h
	and edx,0FFFF0000h
	xor ecx,eax
	mov eax,r9d
	or ecx,edx
	shr eax,10h
	xor ax,r9w
	xor ecx,33D3075Dh
	mov [rsp],ecx
	and r9d,0FFFF0000h
	ror ax,08h
	movzx ecx,ax
	or ecx,r9d
	add ecx,0B23CB27Dh
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	rol dx,08h
	xor ax,cx
	ror ax,08h
	movzx ecx,ax
	movzx eax,dx
	shl eax,10h
	or ecx,eax
	xor ecx,4DC34D83h
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_gobjects ENDP

decrypt_uworld PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	lea eax,[rcx+6FE3151Eh]
	shr rcx,20h
	add ecx,5125AAF0h
	mov [rsp],eax
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_uworld ENDP

decrypt_gameinst PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	lea eax,[rcx+7B1B2F95h]
	xor eax,7B1B2F95h
	shr rcx,20h
	sub ecx,058B054Bh
	mov [rsp],eax
	xor ecx,058B054Bh
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_gameinst ENDP

decrypt_level PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	mov r8,rdx
	shr rcx,20h
	shr r8,20h
	mov eax,edx
	and edx,0EAEAEAEAh
	and ecx,0EAEAEAEAh
	and eax,15151515h
	and r8d,15151515h
	xor edx,eax
	xor ecx,r8d
	sub edx,74D4007Bh
	add ecx,0A640AA5h
	xor edx,8B2BFF85h
	xor ecx,0F59BF55Bh
	mov [rsp],edx
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_level ENDP

decrypt_actors PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	mov r8,rdx
	mov r9,rdx
	shr r8,20h
	shr r9,20h
	mov ecx,edx
	shr r9d,10h
	shr ecx,10h
	xor r8w,r9w
	movzx eax,cx
	xor ax,dx
	rol cx,08h
	movzx ecx,cx
	shl ecx,10h
	movzx eax,ax
	or ecx,eax
	ror r8w,08h
	add ecx,13B3677Dh
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	mov eax,r9d
	xor ecx,13B3677Dh
	shl eax,10h
	mov [rsp],ecx
	movzx ecx,r8w
	or ecx,eax
	add ecx,925C929Dh
	mov eax,ecx
	shr eax,10h
	movzx edx,ax
	rol ax,08h
	xor dx,cx
	movzx ecx,ax
	ror dx,08h
	movzx eax,dx
	shl ecx,10h
	or ecx,eax
	xor ecx,6DA36D63h
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_actors ENDP

decrypt_local PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov r10,rcx
	mov ecx,r10d
	shr ecx,10h
	mov r8,r10
	movzx eax,cx
	shr r8,20h
	rol ax,08h
	movzx edx,ax
	shl edx,10h
	movzx eax,r10w
	xor ecx,eax
	or edx,ecx
	add edx,0B35387DDh
	movzx eax,dx
	mov ecx,edx
	shr ecx,10h
	and edx,0FFFF0000h
	xor ecx,eax
	mov eax,r8d
	or ecx,edx
	shr eax,10h
	xor ax,r8w
	xor ecx,0B35387DDh
	ror ax,08h
	and r8d,0FFFF0000h
	mov [rsp],ecx
	movzx ecx,ax
	or ecx,r8d
	add ecx,32BC32FDh
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	xor dx,cx
	rol ax,08h
	movzx r8d,ax
	ror dx,08h
	shl r8d,10h
	movzx eax,dx
	or r8d,eax
	xor r8d,0CD43CD03h
	mov [rsp+4h],r8d
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_local ENDP

decrypt_controller PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rax,rcx
	ror ecx,08h
	sub ecx,5838D457h
	shr rax,20h
	ror ecx,08h
	add eax,26082649h
	xor ecx,0A7C72BA9h
	xor eax,0D9F7D9B7h
	mov [rsp],ecx
	mov [rsp+4h],eax
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_controller ENDP


decrypt_property PROC
	cmp rcx, 0h
	jz decrypt_failure
	call decrypt_level
	ret
decrypt_property ENDP

decrypt_objectid PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rbx,rcx
	xor ebx,0A054EE71h
	ror ebx,0Ah
	mov eax,ebx
	shl eax,10h
	xor eax,48382C5Eh
	xor eax,ebx
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_objectid ENDP

decrypt_failure PROC
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	mov rax, 0h
	MOV RSP, RBP
	POP RBX
	POP RBP
	ret
decrypt_failure ENDP


END