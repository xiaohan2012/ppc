	vmovsd	(%rax), %xmm5
	vmovsd	8(%rax), %xmm6
	vfmadd231sd	(%rdx), %xmm5, %xmm0
	vmovsd	16(%rax), %xmm7
	vmovsd	24(%rax), %xmm5
	vfmadd231sd	8(%rdx), %xmm6, %xmm3
	vfmadd231sd	16(%rdx), %xmm7, %xmm2
	vfmadd231sd	24(%rdx), %xmm5, %xmm1
