.CODE


decrypt_class PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;	
	mov rax,07884F7513170C40h
	xor rcx,rax
	rol rcx,0Ah
	mov rax,rcx
	shl rax,20h
	mov r8,3403E2CC2A1EC976h
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
	mov rdx,3B918546FC10D7C3h
	xor rcx,rdx
	rol rcx,20h
	mov rax,rcx
	shl rax,20h
	mov rdx,24B7FFB358BAD551h
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
	mov r9,rcx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	ror ax,08h
	movzx eax,ax
	or ecx,eax
	shr r9,20h
	add ecx,3E7E8662h
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	xor dx,cx
	ror dx,08h
	ror ax,08h
	movzx r8d,ax
	movzx eax,dx
	shl r8d,10h
	or r8d,eax
	movzx ecx,r9w
	xor r8d,3E7E8662h
	mov [rsp],r8d
	mov r8d,r9d
	shr r8d,10h
	xor ecx,r8d
	movzx eax,r8w
	ror ax,08h
	movzx edx,ax
	shl edx,10h
	or edx,ecx
	add edx,3D213DA2h
	mov ecx,edx
	movzx eax,dx
	shr ecx,10h
	and edx,0FFFF0000h
	xor ecx,eax
	or ecx,edx
	xor ecx,0C2DEC25Eh
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
	lea eax,[rcx+739E8A8Fh]
	shr rcx,20h
	rol eax,08h
	sub ecx,1BC02A88h
	sub eax,1D61F180h
	ror ecx,10h
	ror eax,10h
	sub ecx,2E6FCBF7h
	xor eax,0DFFF83F1h
	ror ecx,08h
	xor ecx,0A1AFA16Fh
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
	lea eax,[rcx+6B0B5FA5h]
	xor eax,6B0B5FA5h
	shr rcx,20h
	sub ecx,157B153Bh
	mov [rsp],eax
	xor ecx,157B153Bh
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
	and edx,0F0F0F0Fh
	and ecx,0F0F0F0Fh
	and eax,0F0F0F0F0h
	and r8d,0F0F0F0F0h
	xor edx,eax
	xor ecx,r8d
	sub edx,29E941B6h
	sub ecx,2AF62A76h
	xor edx,0D616BE4Ah
	xor ecx,2AF62A76h
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
	mov rax,rcx
	shr rcx,20h
	xor eax,0A90403BDh
	ror eax,08h
	xor ecx,0E33C6E8h
	add eax,44C4B47Ch
	xor eax,440403BDh
	ror eax,08h
	xor eax,44C4B47Ch
	mov [rsp],eax
	lea eax,[rcx+43FB43FCh]
	xor eax,15377AECh
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
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r9,rdx
	shr ecx,10h
	xor ecx,eax
	shr r9,20h
	and edx,0FFFF0000h
	or edx,ecx
	add edx,0BEFE06E2h
	mov ecx,edx
	shr ecx,10h
	movzx eax,cx
	ror ax,08h
	movzx r8d,ax
	movzx eax,dx
	xor ecx,eax
	shl r8d,10h
	or r8d,ecx
	mov eax,r9d
	shr eax,10h
	xor r8d,0BEFE06E2h
	xor r9w,ax
	mov [rsp],r8d
	ror ax,08h
	movzx eax,ax
	shl eax,10h
	ror r9w,08h
	movzx edx,r9w
	or edx,eax
	add edx,0BDA1BD22h
	mov eax,edx
	shr eax,10h
	xor ax,dx
	and edx,0FFFF0000h
	ror ax,08h
	movzx ecx,ax
	or ecx,edx
	xor ecx,425E42DEh
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
	shr rax,20h
	xor ecx,686EFC42h
	xor eax,033F3917h
	not ecx
	not eax
	sub ecx,4D8D5552h
	xor ecx,80E3A913h
	sub eax,4E124E92h
	xor eax,0D9D2887Ah
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
	xor ebx,2BB8DE1Dh
	rol ebx,04h
	mov eax,ebx
	shl eax,10h
	xor eax,ebx
	xor eax,0A8F8E788h
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
	rol ecx,0Ch
	mov eax,ecx
	shl eax,10h
	xor eax,ecx
	xor eax,0F8A8144Eh
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