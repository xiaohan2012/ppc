	vmovsd	(%rax), %xmm6
	vmovsd	8(%rax), %xmm7
	vfmadd231sd	(%rdx), %xmm6, %xmm0
	vmovsd	16(%rax), %xmm5
	vmovsd	24(%rax), %xmm6
	vfmadd231sd	8(%rdx), %xmm7, %xmm3
	vfmadd231sd	16(%rdx), %xmm5, %xmm2
	vfmadd231sd	24(%rdx), %xmm6, %xmm1

