.CODE

decrypt_uworld PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	lea eax,[rcx-09C9A1D6h]
	xor eax,0F6365E2Ah
	shr rcx,20h
	sub ecx,0A160A96h
	mov [rsp],eax
	xor ecx,0A160A96h
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
	xor eax,0C8E6FC42h
	shr rcx,20h
	not eax
	xor ecx,63B73917h
	add eax,5212CA0Eh
	not ecx
	xor eax,800BC9B3h
	add ecx,514D51CEh
	xor ecx,99FA68DAh
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
	not eax
	add eax,41211DEFh
	xor eax,0BEDEE210h
	mov [rsp],eax
	shr rcx,20h
	mov rax,rcx
	rol eax,08h
	not eax
	sub eax,3F713FB1h
	rol eax,08h
	xor eax,0C08EC04Eh
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
	xor eax,074973EBh
	add eax,6A2A8276h
	xor ecx,54C8A658h
	xor eax,0D063F19Dh
	add ecx,69B56936h
	xor ecx,91823092h
	mov [rsp],eax
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
	mov rax,rcx
	lea ecx,[rax+0E1903BDh]
	shr rax,20h
	add eax,7348C6E8h
	rol ecx,10h
	ror eax,08h
	add ecx,1262A904h
	sub eax,08D05071h
	rol ecx,10h
	xor ecx,6949A547h
	ror eax,08h
	xor eax,17191759h
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
	add eax,39968A8Fh
	not ecx
	not eax
	sub ecx,55C82A88h
	add eax,5DBD4913h
	not ecx
	not eax
	sub ecx,23CD230Dh
	sub eax,37697571h
	not ecx
	xor eax,0A242B6ECh
	add ecx,3937D578h
	xor ecx,0DC32DCF2h
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
	xor ebx,0F1E70422h
	ror ebx,0Eh
	mov eax,ebx
	shl eax,10h
	xor eax,2B9C93FDh
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