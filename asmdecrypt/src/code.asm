.CODE


decrypt_class PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;	
	mov rax,0FF4CDCD1935B2DD7h
	xor rcx,rax
	rol rcx,0Ch
	mov rax,rcx
	shl rax,20h
	mov r8,11B34D11D1DA0E66h
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
	mov rdx,415C172E4CA34460h
	xor rcx,rdx
	ror rcx,1Ah
	mov rax,rcx
	shl rax,20h
	mov rdx,448278767E1DA428h
	xor rax,rdx
	xor rax,rcx
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
	mov eax,ecx
	ror eax,08h
	sub eax,48280467h
	shr rcx,20h
	ror eax,08h
	add ecx,36F83639h
	xor eax,0B7D7FB99h
	xor ecx,0C907C9C7h
	mov [rsp],eax
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
	mov eax,ecx
	xor eax,29BB03BDh
	shr rcx,20h
	ror eax,10h
	xor ecx,8EEAC6E8h
	sub eax,3BBBCB04h
	ror ecx,08h
	xor eax,0C4BB03BDh
	sub ecx,3C843C84h
	ror eax,10h
	xor ecx,29EAC6E8h
	xor eax,0C44434FCh
	ror ecx,08h
	xor ecx,3C843C84h
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
	lea eax,[rcx-29E941B6h]
	xor eax,0D616BE4Ah
	shr rcx,20h
	sub ecx,2AF62A76h
	mov [rsp],eax
	xor ecx,2AF62A76h
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
	mov rax,rcx
	shr rcx,20h
	add eax,0E3548A8Fh
	rol eax,08h
	sub eax,7E7B81B0h
	ror eax,10h
	xor eax,0F2FF3C1h
	mov [rsp],eax
	lea eax,[rcx+54F5D578h]
	ror eax,10h
	add eax,721663D9h
	ror eax,08h
	xor eax,71DF719Fh
	mov [rsp+4h],eax
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
	mov r10,rax
	mov r9,rax
	shr r10,20h
	shr r9,20h
	mov ecx,eax
	shr r9d,10h
	shr ecx,10h
	xor r10w,r9w
	xor ax,cx
	ror ax,08h
	shl ecx,10h
	movzx eax,ax
	or eax,ecx
	ror r9w,08h
	add eax,4E8E5652h
	mov ecx,eax
	shr ecx,10h
	movzx edx,cx
	ror cx,08h
	xor dx,ax
	movzx r8d,cx
	shl r8d,10h
	ror dx,08h
	movzx eax,dx
	or r8d,eax
	movzx ecx,r9w
	shl ecx,10h
	xor r8d,4E8E5652h
	movzx eax,r10w
	or ecx,eax
	mov [rsp],r8d
	add ecx,4D114D92h
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	xor ecx,0B2EEB26Eh
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
	mov eax,ecx
	ror eax,08h
	add eax,37577B19h
	shr rcx,20h
	ror eax,08h
	sub ecx,49874947h
	xor eax,37577B19h
	xor ecx,49874947h
	mov [rsp],eax
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
	lea eax,[rcx+2BCB1FE5h]
	xor eax,2BCB1FE5h
	shr rcx,20h
	sub ecx,553B55FBh
	mov [rsp],eax
	xor ecx,553B55FBh
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
	xor ebx,43718069h
	rol ebx,02h
	mov eax,ebx
	shl eax,10h
	xor eax,ebx
	xor eax,0A3997F4Ch
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
	rol ecx,0Ah
	mov eax,ecx
	shl eax,10h
	xor eax,ecx
	xor eax,99A3FE9Dh
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