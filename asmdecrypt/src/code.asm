.CODE

decrypt_outer PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;

	mov rdx,1B0CD93CEFDD0812h
	xor rcx,rdx
	ror rcx,1Eh
	mov rax,rcx
	shl rax,20h
	mov rdx,0FD9EE5651C35118Bh
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
	shr rdx,20h
	not eax
	not edx
	sub eax,66697571h
	add edx,0A37D578h
	not eax
	not edx
	add eax,3D9DA933h
	sub edx,43AD43EDh
	not edx
	not eax
	sub edx,66C82A88h
	add eax,28968A8Fh
	xor eax,0C26256CCh
	xor edx,0BC52BC12h
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
	mov eax,ecx
	xor eax,0A74973EBh
	shr rcx,20h
	add eax,0ACAA2D6h
	xor ecx,0F4C8A658h
	xor eax,5083D13Dh
	add ecx,09150996h
	xor ecx,51225032h
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
	shr rcx,20h
	xor eax,491903BDh
	xor ecx,0AE48C6E8h
	sub eax,1B9B2B24h
	rol ecx,08h
	xor eax,007DD761h
	sub ecx,1CA41CA4h
	mov [rsp],eax
	xor ecx,4948C6E8h
	rol ecx,08h
	xor ecx,1CA41CA4h
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
	add eax,0A527A8D5h
	xor eax,95F5A15Bh
	mov [rsp],eax
	lea eax,[rcx-11F45DF5h]
	xor eax,0EB85EBC5h
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
	add eax,60FDA54Eh
	xor eax,0D0D09030h
	mov [rsp],eax
	lea eax,[rcx+409F7A20h]
	xor eax,30D030D0h
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
	shr rcx,20h
	not eax
	add eax,19968A8Fh
	not ecx
	sub ecx,75C82A88h
	not eax
	sub eax,42E2D64Dh
	not ecx
	add ecx,3CD23C93h
	not eax
	sub eax,57697571h
	not ecx
	xor eax,42E2D64Ch
	add ecx,1937D578h
	xor ecx,3CD23C92h
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
	mov rax,rcx
	mov ecx,eax
	shr rax,20h
	not ecx
	rol eax,08h
	sub ecx,4E6E3281h
	not eax
	xor ecx,4E6E3280h
	add eax,301E30DFh
	mov [rsp],ecx
	rol eax,08h
	xor eax,301E30DEh
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
	xor ebx,54231926h
	rol ebx,06h
	mov eax,ebx
	shl eax,10h
	xor eax,17FA96C4h
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
	ror ecx,02
	mov eax,ecx
	shl eax,10h
	xor eax,ecx
	xor eax,3848AAEDh
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