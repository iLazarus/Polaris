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
	lea eax,[rcx-79395166h]
	xor eax,86C6AE9Ah
	shr rcx,20h
	sub ecx,7AA67A26h
	mov [rsp],eax
	xor ecx,7AA67A26h
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
	ror eax,08h
	sub eax,28086487h
	shr rcx,20h
	ror eax,08h
	add ecx,56D85619h
	xor eax,0D7F79B79h
	xor ecx,0A927A9E7h
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
	mov rax,rcx
	shr rcx,20h
	ror eax,08h
	not ecx
	not eax
	add eax,11F1AD1Fh
	sub ecx,6F416F81h
	ror eax,08h
	xor eax,0EE0E52E0h
	xor ecx,90BE907Eh
	mov [rsp],eax
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
	add eax,935C8A8Fh
	rol eax,08h
	sub eax,5E03D220h
	ror eax,10h
	xor eax,7F9FA351h
	mov [rsp],eax
	lea eax,[rcx+04FDD578h]
	ror eax,10h
	sub eax,6D512B97h
	ror eax,08h
	xor eax,014F010Fh
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
	lea ecx,[rax-61FBFC43h]
	shr rax,20h
	add eax,0333C6E8h
	rol ecx,10h
	ror eax,08h
	add ecx,32DDF974h
	add eax,168A3EFFh
	rol ecx,10h
	xor ecx,0F9D9F5B7h
	ror eax,08h
	xor eax,87A987E9h
	mov [rsp],ecx
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
	mov eax,ecx
	not eax
	shr rcx,20h
	sub eax,76447571h
	not ecx
	not eax
	sub ecx,05A32A88h
	sub eax,12B2667Dh
	not ecx
	not eax
	add ecx,6CA26C63h
	add eax,18BB8A8Fh
	not ecx
	xor eax,12B2667Ch
	sub ecx,76A32A88h
	xor ecx,6CA26C62h
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
	xor ebx,0B0E02451h
	ror ebx,0Dh
	mov eax,ebx
	shl eax,10h
	xor eax,ebx
	xor eax,0D624842Ch
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