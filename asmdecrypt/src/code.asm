.CODE


decrypt_gobjects PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	lea eax,[rdx+36769EEAh]
	shr rdx,20h
	xor eax,36769EEAh
	add edx,35A9352Ah
	mov [rsp],eax
	xor edx,0CA56CAD6h
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
	mov eax,ecx
	ror eax,8h
	sub eax,6848A447h
	shr rcx,20h
	ror eax,8h
	add ecx,16181659h
	xor eax,97B75BB9h
	xor ecx,0E9E7E9A7h
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
	mov eax,ecx
	ror eax,8h
	sub eax,5838D457h
	shr rcx,20h
	ror eax,8h
	add ecx,26082649h
	xor eax,0A7C72BA9h
	xor ecx,0D9F7D9B7h
	mov [rsp],eax
	mov [rsp+4h], ecx
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
	shl ecx,10h
	ror ax,08h
	movzx edx,ax
	or edx,ecx
	add edx,8ECE9612h
	mov eax,edx
	shr eax,10h
	xor dx,ax
	ror ax,08h
	movzx ecx,ax
	shl ecx,10h
	ror dx,08h
	movzx eax,dx
	or ecx,eax
	movzx eax,r8w
	xor ecx,8ECE9612h
	ror r8w,08h
	mov [rsp],ecx
	xor ax,r9w
	movzx eax,ax
	movzx ecx,r8w
	shl ecx,10h
	or ecx,eax
	add ecx,8DD18D52h
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	xor ecx,722E72AEh
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
	not eax
	sub eax,1E3EC2B1h
	xor eax,1E3EC2B0h
	mov [rsp],eax
	shr rcx,20h
	mov rax,rcx
	rol eax,08h
	not eax
	add eax,60EE60AFh
	rol eax,08h
	xor eax,60EE60AEh
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
	lea eax,[rcx-4909E196h]
	shr rcx,20h
	xor eax,0B6F61E6Ah
	sub ecx,4AD64A56h
	mov [rsp],eax
	xor ecx,4AD64A56h
	mov [rsp+4h],ecx
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
	mov eax,ecx
	xor eax,07C873EBh
	shr rcx,20h
	add eax,6A2A8276h
	xor ecx,5447A658h
	xor eax,0D0E2F19Dh
	add ecx,69B56936h
	xor ecx,910D3092h
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
	mov rbx,rcx
	xor ebx,1D0C0BAFh
	ror ebx,04h
	mov eax,ebx
	shl eax,10h
	xor eax,32B10C0Ah
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