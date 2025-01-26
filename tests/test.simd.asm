.data
ALIGN 8
i0 dd 0, 0, 0, 0, 0, 0, 0, 0
ALIGN 8
i1 dd 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216
ALIGN 8
i2 dd 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406
ALIGN 8
i3 dd 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584
PUBLIC out_buffer
PUBLIC in_buffer
out_buffer DD 128 DUP(0)
in_buffer DD 36 DUP(0)

.code
PUBLIC GO
GO PROC EXPORT

mov eax, in_buffer[0]
vmovd xmm0, eax
vbroadcastss ymm0, xmm0
; Free $0



; stack $0 -> ymm1
vmovdqu ymm1, ymmword ptr [rbx]
; vmovups $1, $-1
vmovups ymm0, in_buffer[4]


push rbp
mov rbp, rsp
sub rsp, 1024
mov rbx, rsp


; stack $0 -> ymm0 | $1 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0

; vcvtdq2ps $7, $0
vcvtdq2ps ymm1, ymm0
; Free $0


; Free $18446744073709551615



; stack $0 -> ymm1 | $7 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm1

; vmovaps $8, $1024
vmovaps ymm0, i0
; Free $0



; stack $1 -> ymm0 | $8 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0


; stack $0 -> ymm2
vmovdqu ymm2, ymmword ptr [rbx]
; vmovaps $9, $1
vmovaps ymm1, ymm0

; stack $0 -> ymm0 | $1 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0

; vmovaps $10, $1
vmovaps ymm2, ymm0
; Free $9


; Free $0



; stack $0 -> ymm1
vmovdqu ymm1, ymmword ptr [rbx]
; vmovaps $11, $1025
vmovaps ymm0, i1
; vmulps $12, $9, $10
vmulps ymm1, ymm3, ymm2
; Free $9


; Free $18446744073709551615


; vaddps $13, $12, $11
vaddps ymm3, ymm1, ymm0
; Free $18446744073709551615


; Free $18446744073709551615


; vaddps $14, $13, $1025
vaddps ymm4, ymm3, i1
; Free $18446744073709551615



; stack $7 -> ymm0 | $11 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0


; stack $0 -> ymm1 | $12 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm1

; vmovaps $4, $7
vmovaps ymm5, ymm0
; Free $0


; vaddps $15, $14, $1025
vaddps ymm1, ymm4, i1
; Free $18446744073709551615


; vdivps $3, $7, $1026
vdivps ymm6, ymm0, i2
; Free $18446744073709551615


; vaddps $16, $15, $1025
vaddps ymm7, ymm1, i1
; vaddps $17, $16, $1025
vaddps ymm8, ymm7, i1
; Free $18446744073709551615


; vaddps $18, $17, $1025
vaddps ymm9, ymm8, i1
; Free $1


; vaddps $19, $18, $1025
vaddps ymm10, ymm9, i1
; Free $12



; stack $8 -> ymm0 | $7 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0


; stack $0 -> ymm1 | $15 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm1

; vmovaps $8, $19
vmovaps ymm0, ymm10
; Free $8


; Free $18446744073709551615


; Free $0



; stack $0 -> ymm2 | $10 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm2

; vmovaps $2, $8
vmovaps ymm0, ymm1
; Free $8


; Free $0



; stack $7 -> ymm0 | $2 -> stack 
vmovdqu ymm15, ymmword ptr [rbx]
vmovdqu ymmword ptr [rbx], ymm0

; vmulps $5, $7, $1027
vmulps ymm1, ymm0, i3
; Free $7




; stack $2 -> ymm0
vmovdqu ymm0, ymmword ptr [rbx]

; stack $0 -> ymm0
vmovdqu ymm0, ymmword ptr [rbx]
; vmovaps $-1, $2
vmovaps out_buffer[0], ymm0

; stack $0 -> ymm0
vmovdqu ymm0, ymmword ptr [rbx]
; vmovaps $-1, $3
vmovaps out_buffer[32], ymm6
; Free $13



; stack $0 -> ymm0
vmovdqu ymm0, ymmword ptr [rbx]
; vmovaps $-1, $4
vmovaps out_buffer[64], ymm5
; Free $14



; stack $0 -> ymm0
vmovdqu ymm0, ymmword ptr [rbx]
; vmovaps $-1, $5
vmovaps out_buffer[96], ymm1
; Free $4



mov rsp, rbp
pop rbp


GO ENDP
DllMain PROC hinstDLL:QWORD, fdwReason:QWORD, lpReserved:QWORD
mov  eax, 1
ret
DllMain ENDP
END