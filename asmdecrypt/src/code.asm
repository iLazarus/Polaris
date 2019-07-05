.CODE

decrypt_uworld PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov eax,ecx
	xor eax,09BB03BDh
	shr rcx,20h
	ror eax,10h
	xor ecx,6EEAC6E8h
	sub eax,5BDB6BE4h
	ror ecx,08h
	xor eax,0A4BB03BDh
	sub ecx,5C645C64h
	ror eax,10h
	xor ecx,09EAC6E8h
	xor eax,0A424941Ch
	ror ecx,08h
	xor ecx,5C645C64h
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
	rol eax,10h
	shr rcx,20h
	sub eax,038373BCh
	ror ecx,08h
	rol eax,10h
	sub ecx,043C043Ch
	xor eax,0FC7C8C44h
	ror ecx,08h
	xor ecx,043C043Ch
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
	add eax,43548A8Fh
	rol eax,08h
	sub eax,3E9C2190h
	ror eax,10h
	xor eax,0EF0F53E1h
	mov [rsp],eax
	lea eax,[rcx-4B0A2A88h]
	ror eax,10h
	sub eax,4DC9BC07h
	ror eax,08h
	xor eax,91BF917Fh
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
	xor eax,1844FC42h
	not eax
	xor ecx,0B3153917h
	add eax,02C2BA5Eh
	not ecx
	xor eax,8079B9E3h
	add ecx,019D011Eh
	xor ecx,1988380Ah
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
	mov eax,ecx
	ror eax,08h
	add eax,1737DB39h
	shr rcx,20h
	ror eax,08h
	sub ecx,69676927h
	xor eax,1737DB39h
	xor ecx,69676927h
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
	lea eax,[rcx+0BAB7F05h]
	xor eax,0BAB7F05h
	shr rcx,20h
	sub ecx,751B75DBh
	mov [rsp],eax
	xor ecx,751B75DBh
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
	xor ebx,03709FEDh
	ror ebx,08h
	mov eax,ebx
	shl eax,10h;
	xor eax,3A58F24Bh;
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