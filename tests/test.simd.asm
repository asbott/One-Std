.data
ALIGN 8
i0 dd 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216, 1065353216
ALIGN 8
i1 dd 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406, 1076258406
ALIGN 8
i2 dd 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584, 1084227584
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
vmovups ymm1, in_buffer[4]


push rbp
mov rbp, rsp
sub rsp, 512

vcvtdq2ps ymm7, ymm0
vmulps ymm15, ymm1, ymm1
vaddps ymm8, ymm15, i0
vmovaps ymm2, ymm8
vdivps ymm3, ymm7, i1
vmovaps ymm4, ymm7
vmulps ymm5, ymm7, i2

mov rsp, rbp
pop rbp


vmovaps out_buffer[0], ymm2
vmovaps out_buffer[32], ymm3
vmovaps out_buffer[64], ymm4
vmovaps out_buffer[96], ymm5

GO ENDP
DllMain PROC hinstDLL:QWORD, fdwReason:QWORD, lpReserved:QWORD
mov  eax, 1
ret
DllMain ENDP
END