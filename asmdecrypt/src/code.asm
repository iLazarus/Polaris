.CODE


decrypt_class PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;	
	mov rax,3F4A1AB0EBE74904h
	xor rcx,rax
	rol rcx,20h
	mov rax,rcx
	shl rax,20h
	mov r8,0AAC0347167E6EEACh
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
	mov rdx,5D9B32870F5D5E8Dh
	xor rcx,rdx
	rol rcx,0Ah
	mov rax,rcx
	shl rax,20h
	mov rdx,0A20B4F0FC5C83682h
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
	mov rdx,rcx
	mov eax,edx
	ror eax,08h
	shr rdx,20h
	not eax
	sub eax,3E5E6291h
	not edx
	ror eax,08h
	xor eax,3E5E6290h
	add edx,400E40CFh
	xor edx,400E40CEh
	mov [rsp],eax
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
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r9,rdx
	shr ecx,10h
	xor ecx,eax
	shr r9,20h
	and edx,0FFFF0000h
	or ecx,edx
	add ecx,0CE0ED6D2h
	mov edx,ecx
	movzx ecx,cx
	shr edx,10h
	xor ecx,edx
	movzx eax,dx
	ror ax,08h
	mov edx,r9d
	shr edx,10h
	movzx r8d,ax
	movzx eax,dx
	ror ax,08h
	xor dx,r9w
	ror dx,08h
	shl r8d,10h
	or r8d,ecx
	movzx edx,dx
	movzx ecx,ax
	xor r8d,0CE0ED6D2h
	shl ecx,10h
	or edx,ecx
	mov [rsp],r8d
	add edx,0CD91CD12h
	mov eax,edx
	shr eax,10h
	xor ax,dx
	and edx,0FFFF0000h
	ror ax,08h
	movzx ecx,ax
	or ecx,edx
	xor ecx,326E32EEh
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
	shr rcx,20h
	not eax
	rol ecx,08h
	add eax,31114DFFh
	not ecx
	xor eax,0CEEEB200h
	sub ecx,4F614FA1h
	mov [rsp],eax
	rol ecx,08h
	xor ecx,0B09EB05Eh
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
	add eax,0BED003BDh
	rol eax,10h
	add eax,73C99954h
	rol eax,10h
	xor eax,19F99597h
	mov [rsp],eax
	lea eax,[rcx+23FFC6E8h]
	ror eax,08h
	add eax,57365FDFh
	ror eax,08h
	xor eax,67C96709h
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
	shr rcx,20h
	add eax,7F8F85EEh
	xor eax,303070D0h
	mov [rsp],eax
	lea eax,[rcx+6270DAC0h]
	xor eax,0D030D030h
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
	mov eax,ecx
	ror eax,08h
	not eax
	shr rcx,20h
	add eax,41211DEFh
	not ecx
	ror eax,08h
	sub ecx,3F713FB1h
	xor eax,0BEDEE210h
	xor ecx,0C08EC04Eh
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
	lea eax,[rcx-79CA36CBh]
	xor eax,3595C1BBh
	shr rcx,20h
	sub ecx,3025BD95h
	mov [rsp],eax
	xor ecx,4B254B65h
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
	xor ebx,0DADC8D26h
	rol ebx,0Eh
	mov eax,ebx
	shl eax,10h
	xor eax,ebx
	xor eax,0E5F9FF4Ah
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