.CODE

decrypt_uworld PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	lea eax,[rcx-7CA37571h]
	shr rcx,20h
	rol eax,08h
	sub ecx,0B022A88h
	add eax,41AC1E30h
	ror ecx,10h
	ror eax,10h
	add ecx,31FE83B9h
	xor eax,2F4F93A1h
	ror ecx,08h
	xor ecx,51FF51BFh
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
	lea eax,[rcx-31CCFC43h]
	shr rcx,20h
	rol eax,10h
	add ecx,3362C6E8h
	sub eax,6DC396BCh
	ror ecx,08h
	rol eax,10h
	add ecx,76896FCFh
	xor eax,29096587h
	ror ecx,08h
	xor ecx,57D95719h
	mov [rsp],eax
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
	mov r8,rcx
	shr rcx,20h
	shr r8,20h
	mov eax,edx

	and edx,0F0F0F0Fh
	and ecx,0F0F0F0Fh
	and eax,0F0F0F0F0h
	and r8d,0F0F0F0F0h
	xor edx,eax
	xor ecx,r8d
	add edx,2666CEFAh
	add ecx,25B9253Ah
	xor edx,2666CEFAh
	xor ecx,0DA46DAC6h
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
	add ecx,23C3376Dh
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	mov eax,r9d
	xor ecx,23C3376Dh
	shl eax,10h
	mov [rsp],ecx
	movzx ecx,r8w
	or ecx,eax
	add ecx,0A24CA28Dh
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
	xor ecx,5DB35D73h
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
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r9,rdx
	shr ecx,10h
	xor ecx,eax
	shr r9,20h
	and edx,0FFFF0000h
	or edx,ecx
	add edx,4E8E5652h
	mov ecx,edx
	shr ecx,10h
	movzx eax,cx
	ror ax,08h
	movzx r8d,ax
	movzx eax,dx
	mov edx,r9d
	xor ecx,eax
	shr edx,10h
	movzx eax,dx
	shl r8d,10h
	xor ax,r9w
	ror dx,08h
	ror ax,08h
	or r8d,ecx
	movzx ecx,ax
	xor r8d,4E8E5652h
	movzx edx,dx
	shl edx,10h
	or edx,ecx
	mov [rsp],r8d
	add edx,4D114D92h
	mov eax,edx
	shr eax,10h
	xor ax,dx
	and edx,0FFFF0000h
	ror ax,08h
	movzx ecx,ax
	or ecx,edx
	xor ecx,0B2EEB26Eh
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
	mov rax,rcx
	mov ecx,eax
	shr rax,20h
	xor ecx,0D8CCFC42h
	xor eax,739D3917h
	not ecx
	not eax
	add ecx,4202FA1Eh
	xor ecx,8031F9A3h
	add eax,415D41DEh
	xor eax,99C078CAh
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
	xor ebx,46270166h
	ror ebx,0Ah
	mov eax,ebx
	shl eax,10h
	xor eax,70681B93h
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