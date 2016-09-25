/*
 *
 * Carina
 * Software Multitasking Handler
 *
 * Copyright (C) 2015 Bastiaan Teeuwen <bastiaan.teeuwen170@gmail.com>
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

#include <system.h>

void svmode_enter(void)
{
	
}

void usrmode_func(void)
{
	for (;;)
		asm volatile ("hlt");
}

void usrmode_enter(void)
{
	asm volatile (" \
				   cli; \
				   mov $0x20, %ax; \
				   mov %ax, %dx; \
				   mov %ax, %es; \
				   mov %ax, %fs; \
				   mov %ax, %gs; \
				   \
				   mov %rsp, %rax; \
				   push $0x20; \
				   push %rax; \
				   pushf; \
				   push $0x18; \
				   push $0; \
				   iretq; \
				   1: \
				   ");
}