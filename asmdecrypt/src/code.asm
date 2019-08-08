.CODE


decrypt_class PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;	
	mov rax,6FBFB5F4988B0F16h
	xor rcx,rax
	ror rcx,1Bh
	mov rax,rcx
	shl rax,20h
	mov r8,49EA8283457AE95Fh
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
	mov r8,0B5DB00F8BAC3E82Dh
	xor rcx,r8
	rol rcx,0Fh
	mov rbx,rcx
	shl rbx,20h
	mov rax,80B3B03A3797034Ah
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
	mov eax,edx
	shr rdx,20h
	xor eax,99FF03BDh
	xor edx,0FE2EC6E8h
	ror eax,10h
	ror edx,08h
	add eax,34B4E48Ch
	add edx,330B330Ch
	xor eax,34FF03BDh
	xor edx,992EC6E8h
	ror eax,10h
	ror edx,08h
	xor eax,34B4E48Ch
	xor edx,0CCF4CCF4h
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
	lea eax,[rcx+6633E895h]
	xor eax,0D535E11Bh
	shr rcx,20h
	sub ecx,52681D35h
	mov [rsp],eax
	xor ecx,0ABC5AB05h
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
	xor eax,0E74F73EBh
	shr rcx,20h
	add eax,4A0AE296h
	xor ecx,34CEA658h
	xor eax,0D045917Dh
	add ecx,49D54956h
	xor ecx,51E410F2h
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
	rol eax,10h
	sub eax,33B3E38Ch
	rol eax,10h
	xor eax,0CC4C1C74h
	mov [rsp],eax
	shr rcx,20h
	mov eax,ecx
	ror eax,08h
	sub eax,340C340Ch
	ror eax,08h
	xor eax,340C340Ch
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
	add ecx,0E383F7ADh
	mov eax,ecx
	shr eax,10h
	xor ax,cx
	and ecx,0FFFF0000h
	movzx eax,ax
	or ecx,eax
	mov eax,r9d
	xor ecx,0E383F7ADh
	shl eax,10h
	mov [rsp],ecx
	movzx ecx,r8w
	or ecx,eax
	add ecx,628C62CDh
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
	xor ecx,9D739D33h
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
	mov ecx,eax
	xor ecx,19FF03BDh
	shr rax,20h
	ror ecx,10h
	xor eax,7E2EC6E8h
	sub ecx,4BCB9BF4h
	ror eax,08h
	xor ecx,0B4FF03BDh
	sub eax,4C744C74h
	ror ecx,10h
	xor eax,192EC6E8h
	xor ecx,0B434640Ch
	ror eax,08h
	xor eax,4C744C74h
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
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r8,rdx
	shr ecx,10h
	xor ecx,eax
	shr r8,20h
	and edx,0FFFF0000h
	or ecx,edx
	add ecx,0A8A808D8h
	movzx eax,cx
	mov edx,ecx
	shr edx,10h
	and ecx,0FFFF0000h
	xor edx,eax
	or edx,ecx
	xor edx,0A8A808D8h
	mov [rsp],edx
	mov edx,r8d
	shr edx,10h
	movzx eax,dx
	xor dx,r8w
	ror ax,08h
	movzx ecx,ax
	rol dx,08h
	movzx eax,dx
	shl ecx,10h
	or ecx,eax
	add ecx,0A7D7A7D8h
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	xor dx,cx
	ror ax,08h
	movzx r8d,ax
	rol dx,08h
	shl r8d,10h
	movzx eax,dx
	or r8d,eax
	xor r8d,58285828h
	mov [rsp+4h],r8d
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
	xor ebx,6BDBCC90h
	rol ebx,0Bh
	mov eax,ebx
	shl eax,10h
	xor eax,ebx
	xor eax,0DA4B6FBFh
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
	xor ecx,38C9736Eh
	rol ecx,03h
	mov eax,ecx
	shl eax,10h
	xor eax,ecx
	xor eax,4BDA3517h
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