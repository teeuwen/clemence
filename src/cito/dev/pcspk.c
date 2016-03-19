/*
 *
 * Carina
 * PC Speaker Driver
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

#include <stdlib.h>

#include <system.h>

void pcspk_play(const u16 freq)
{
	u16 _freq = PIT_FREQ / freq;

	io_outb(PIT_IO, PIT_SPKR);
	io_outb(PIT_CH2_CMD, _freq);
	io_outb(PIT_CH2_CMD, _freq >> 8);

	u8 tmp = io_inb(0x61);
	if (tmp != (tmp | 3)) io_outb(0x61, tmp | 3);
}

void pcspk_stop(void) //TODO Revise
{
	u8 tmp = io_inb(0x61) & 0xFC;
	io_outb(0x61, tmp);
}
