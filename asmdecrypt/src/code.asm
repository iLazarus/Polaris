.CODE


decrypt_class PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;	
	mov rax,0A73963B7AA7BA8B9h
	xor rcx,rax
	ror rcx,0Eh
	mov rax,rcx
	shl rax,20h
	mov r8,55F995CEA822ECD4h
	xor rax,r8
	xor rax,rcx
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_class ENDP

decrypt_outer PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov r8,0E8612C1FD51F717Eh
	xor rcx,r8
	rol rcx,18h
	mov rbx,rcx
	shl rbx,20h
	mov rax,4A705ECC821048F9h
	xor rbx,rax
	xor rbx,rcx
	mov rax,rbx
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_outer ENDP

decrypt_gobjects PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	lea eax,[rdx-3494C0BBh]
	shr rdx,20h
	xor eax,0CB6B3F45h
	add edx,4A244A65h
	mov [rsp],eax
	xor edx,0B5DBB59Bh
	mov [rsp+4h],edx
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
	mov r8d,ecx
	mov r10,rcx
	shr r8d,10h;
	movzx ecx,cx
	movzx eax,r8w
	ror ax,08h;
	xor ecx,r8d
	movzx edx,ax
	shl edx,10h;
	or edx,ecx
	shr r10,20h;
	add edx,0D8D878A8h;
	mov r8d,edx
	movzx ecx,dx
	shr r8d,10h;
	xor ecx,r8d
	movzx eax,r8w
	ror ax,08h;
	movzx r9d,ax
	mov eax,r10d
	shr eax,10h;
	xor ax,r10w
	shl r9d,10h;
	rol ax,08h;
	or r9d,ecx
	movzx edx,ax
	and r10d,0FFFF0000h;
	or edx,r10d
	xor r9d,0D8D878A8h;
	add edx,0D7A7D7A8h;
	mov [rsp],r9d
	mov eax,edx
	shr eax,10h;
	xor ax,dx
	and edx,0FFFF0000h;
	rol ax,08h;
	movzx ecx,ax
	or ecx,edx
	xor ecx,28582858h;
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
	mov r8d,ecx
	mov r10,rcx
	shr r8d,10h
	movzx ecx,cx
	movzx eax,r8w
	ror ax,08h
	xor ecx,r8d
	movzx edx,ax
	shl edx,10h
	or edx,ecx
	shr r10,20h
	add edx,0C8C8A8B8h
	mov r8d,edx
	movzx ecx,dx
	shr r8d,10h
	xor ecx,r8d
	movzx eax,r8w
	ror ax,08h
	movzx r9d,ax
	mov eax,r10d
	shr eax,10h
	xor ax,r10w
	shl r9d,10h
	rol ax,08h
	or r9d,ecx
	movzx edx,ax
	and r10d,0FFFF0000h
	or edx,r10d
	xor r9d,0C8C8A8B8h
	add edx,0C7B7C7B8h
	mov [rsp],r9d
	mov eax,edx
	shr eax,10h
	xor ax,dx
	and edx,0FFFF0000h
	rol ax,08h
	movzx ecx,ax
	or ecx,edx
	xor ecx,38483848h
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
	mov r9,rdx
	mov r8,rdx
	shr r9,20h
	shr r8,20h
	mov ecx,edx
	shr r8d,10h
	shr ecx,10h
	movzx eax,cx
	xor ax,dx
	rol cx,08h
	movzx eax,ax
	movzx ecx,cx
	shl ecx,10h
	or ecx,eax
	add ecx,23C3376Dh
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	movzx eax,r8w
	xor ax,r9w
	xor ecx,023C3376Dh
	ror ax,08h
	movzx edx,ax
	mov eax,r8d
	shl eax,10h
	or edx,eax
	mov [rsp],ecx
	add edx,0A24CA28Dh
	mov eax,edx
	shr eax,10h
	xor dx,ax
	rol ax,08h
	movzx ecx,ax
	ror dx,08h
	shl ecx,10h
	movzx eax,dx
	or ecx,eax
	xor ecx,5DB35D73h
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
	mov rax,rcx
	shr rcx,20h
	add eax,70FB151Eh
	mov [rsp],eax
	lea eax,[rcx+523DAAF0h]
	mov [rsp+4h],eax
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
	mov rax,rcx
	lea ecx,[rax+4BEBBFC5h]
	shr rax,20h
	xor ecx,4BEBBFC5h
	sub eax,355B351Bh
	mov [rsp],ecx
	xor eax,355B351Bh
	mov [rsp+4h],eax
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
	lea eax,[rcx+53FD8A8Fh]
	shr rcx,20h
	rol eax,08h
	sub ecx,3B612A88h
	add eax,225CEE20h
	ror ecx,10h
	ror eax,10h
	add ecx,128F93A9h
	xor eax,3F5F6391h
	ror ecx,08h
	xor ecx,410F41CFh
	mov [rsp],eax
	mov [rsp+4h],ecx
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
	mov ebx,ecx
	xor ebx,791FBDDBh
	ror ebx,04h
	mov eax,ebx
	shl eax,10h
	xor eax,048C6739h
	xor eax,ebx
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_objectid ENDP

decrypt_objectnumber PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	xor ecx,9289564Dh
	ror ecx,0Ch
	mov eax,ecx
	shl eax,10h
	xor eax,ecx
	xor eax,8C04F844h
	;;;;;;;;;;;;;;;;;;;;;;;;;
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_objectnumber ENDP

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