/*
 *
 * Carina
 * src/kernel/arch/x86/boot/entry.S
 *
 * Copyright (C) 2016 Bastiaan Teeuwen <bastiaan.teeuwen170@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 */
 
.code32

//.set KERN_VMA,		0xFFFFFFFF80000000

.section .mboot

.set MB_MAGIC,		0x1BADB002
//.set MB_FLAGS,		(1 << 0) | (1 << 1) | (1 << 2)
.set MB_FLAGS,		(1 << 0) | (1 << 1)

.align 4
mboot_header:
	.long MB_MAGIC
	.long MB_FLAGS
	.long -(MB_MAGIC + MB_FLAGS)

 
.section .text

entry:
	/* Disable interrupts */
	cli

	/* Save the Multiboot info struct */
	/* XXX TODO Store in safer location XXX */
	mov %ebx, %edi

	/* TODO What is this again??? */
	//mov $0xFF, %al
	//outb %al, $0xA1
	//outb %al, $0x21

	/* Check if CPUID is available */
	pushfl
	pop %eax
	bt $21, %eax
	jb nocpuid

#ifdef ARCH_x86_64
	/* Check if extended CPUID is available */
	mov $0x80000000, %eax
	cpuid
	cmp $0x80000001, %eax
	jb nolm

	/* Check if long mode is available */
	mov $0x80000001, %eax
	cpuid
	bt $29, %edx
	jnc nolm
#endif

	/* Disable paging (required by Intel manual) */
	mov %cr0, %eax
	btr $31, %eax /* CR0.PG */
	mov %eax, %cr0

	/* TODO Enable SSE and SSE2 if available */

	/* Enable PAE and SSE */
	mov %cr4, %eax
	bts $5, %eax /* CR4.PAE */
	bts $7, %eax /* CR4.PGE */ /* TEMP */
	//bts $9, %eax /* What does this do again? */
	//bts $10, %eax /* CR4.OSXMMEXCPT */
	mov %eax, %cr4

	//call paging_init
	//mov $0x200000, %eax
	//mov %eax, %cr3

	//call gdt_init

	jmp bootstrap

nocpuid:
	mov $msg_nocpuid, %esi
	jmp early_panic

nolm:
	mov $msg_nolm, %esi
	jmp early_panic

nosse:
	mov $msg_nosse, %esi
	jmp early_panic

nosse2:
	mov $msg_nosse2, %esi
	jmp early_panic

early_panic:
	/* Address and color */
	mov $0xB8000, %ecx
	mov $0x07, %ah

/* Not working */
/*clear_loop:
	mov $0, %al
	cmp $2000, %eax
	je print_loop
	mov %ax, (%ecx)

	add $0x02, %ecx
	inc %eax
	jmp clear_loop*/

print_loop:
	mov (%esi), %al
	cmp $0, %al
	je halt
	mov %ax, (%ecx)

	add $0x02, %ecx
	inc %esi
	jmp print_loop

halt:
	hlt
	jmp halt


.section .rodata

msg_nocpuid:
	.ascii "CPUID is not supported by your processor!\0"
msg_nolm:
	.ascii "Long mode is not supported by your processor!\0"
msg_nosse:
	.ascii "SSE is not supported by your processor!\0"
msg_nosse2:
	.ascii "SSE2 is not supported by your processor!\0"
msg_panic:
	.ascii "Unable to continue. The system has been halted\0"