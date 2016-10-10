/*
 *
 * Carina
 * src/kernel/dev/sound/pcspk.c
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

#include <cpu.h>
#include <timer/pit.h>

void pcspk_play(const u16 freq)
{
	u16 val = PIT_FREQ / freq;

	io_outb(PIT_CMD, PIT_SPKR);
	io_outb(PIT_CH2_IO, val & 0xFF);
	io_outb(PIT_CH2_IO, (val >> 8) & 0xFF);

	u8 spkr = io_inb(0x61);
	if (spkr != (spkr | 3))
		io_outb(0x61, spkr | 3);
}

void pcspk_stop(void)
{
	u8 spkr = io_inb(0x61) & 0xFC;
	io_outb(0x61, spkr);
}

/*
 * This is more something that should be implemented in userspace, this is just
 * here as a temporary goof.
 */

void pcspk_fj(void)
{
	pcspk_play(523);
	sleep(450);
	pcspk_play(587);
	sleep(450);
	pcspk_play(659);
	sleep(450);
	pcspk_play(523);
	sleep(450);
	pcspk_play(523);
	sleep(450);
	pcspk_play(587);
	sleep(450);
	pcspk_play(659);
	sleep(450);
	pcspk_play(523);
	sleep(450);

	pcspk_play(659);
	sleep(450);
	pcspk_play(698);
	sleep(450);
	pcspk_play(783);

	sleep(900);

	pcspk_play(659);
	sleep(450);
	pcspk_play(698);
	sleep(450); 
	pcspk_play(783);

	sleep(900);

	pcspk_play(783);
	sleep(225);
	pcspk_play(880);
	sleep(225);
	pcspk_play(783);
	sleep(225);
	pcspk_play(698);
	sleep(225);
	pcspk_play(659);
	sleep(450);
	pcspk_play(523);

	sleep(450);

	pcspk_play(783);
	sleep(225);
	pcspk_play(880);
	sleep(225);
	pcspk_play(783);
	sleep(225);
	pcspk_play(698);
	sleep(225);
	pcspk_play(659);
	sleep(450);
	pcspk_play(523);

	sleep(450);

	pcspk_play(523);
	sleep(450);
	pcspk_play(391);
	sleep(450);
	pcspk_play(523);
	sleep(900);

	pcspk_play(523);
	sleep(450);
	pcspk_play(391);
	sleep(450);
	pcspk_play(523);
	sleep(600);

	pcspk_stop();
}

void pcspk_mi(void)
{
	pcspk_play(19);
	sleep(50);
	pcspk_play(987);
	sleep(50);
	pcspk_play(659);
	sleep(25);
	pcspk_play(493);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(155);
	sleep(25);
	pcspk_play(19);
	sleep(50);
	pcspk_play(349);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(155);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(155);
	sleep(100);
	pcspk_play(19);
	sleep(25);
	pcspk_play(493);
	sleep(50);
	pcspk_play(19);
	sleep(125);
	pcspk_play(391);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(246);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(246);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(38);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(195);
	sleep(25);
	pcspk_play(220);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(155);
	sleep(25);
	pcspk_play(19);
	sleep(50);
	pcspk_play(195);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(493);
	sleep(25);
	pcspk_play(659);
	sleep(25);
	pcspk_play(138);
	sleep(50);
	pcspk_play(987);
	sleep(25);
	pcspk_play(155);
	sleep(125);
	pcspk_play(138);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(220);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(155);
	sleep(50);
	pcspk_play(19);
	sleep(50);
	pcspk_play(246);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(155);
	sleep(150);
	pcspk_play(493);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(369);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(246);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(138);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(261);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(61);
	sleep(25);
	pcspk_play(195);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(155);
	sleep(25);
	pcspk_play(19);
	sleep(50);
	pcspk_play(195);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(138);
	sleep(125);
	pcspk_play(155);
	sleep(275);
	pcspk_play(19);
	sleep(50);
	pcspk_play(246);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(38);
	sleep(25);
	pcspk_play(659);
	sleep(150);
	pcspk_play(19);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(220);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(659);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(783);
	sleep(150);
	pcspk_play(739);
	sleep(175);
	pcspk_play(659);
	sleep(125);
	pcspk_play(195);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(97);
	sleep(25);
	pcspk_play(659);
	sleep(325);
	pcspk_play(277);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(75);
	pcspk_play(19);
	sleep(25);
	pcspk_play(195);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(75);
	pcspk_play(138);
	sleep(25);
	pcspk_play(97);
	sleep(300);
	pcspk_play(195);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(277);
	sleep(50);
	pcspk_play(19);
	sleep(100);
	pcspk_play(391);
	sleep(25);
	pcspk_play(587);
	sleep(150);
	pcspk_play(523);
	sleep(150);
	pcspk_play(195);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(493);
	sleep(125);
	pcspk_play(195);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(523);
	sleep(175);
	pcspk_play(261);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(195);
	sleep(50);
	pcspk_play(311);
	sleep(25);
	pcspk_play(523);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(493);
	sleep(275);
	pcspk_play(19);
	sleep(75);
	pcspk_play(184);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(77);
	sleep(50);
	pcspk_play(19);
	sleep(75);
	pcspk_play(195);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(77);
	sleep(25);
	pcspk_play(659);
	sleep(25);
	pcspk_play(77);
	sleep(125);
	pcspk_play(19);
	sleep(100);
	pcspk_play(311);
	sleep(50);
	pcspk_play(19);
	sleep(100);
	pcspk_play(659);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(659);
	sleep(75);
	pcspk_play(19);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(50);
	pcspk_play(19);
	sleep(100);
	pcspk_play(493);
	sleep(25);
	pcspk_play(659);
	sleep(300);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(246);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(783);
	sleep(150);
	pcspk_play(739);
	sleep(175);
	pcspk_play(659);
	sleep(150);
	pcspk_play(293);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(195);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(38);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(659);
	sleep(300);
	pcspk_play(195);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(50);
	pcspk_play(123);
	sleep(25);
	pcspk_play(184);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(50);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(277);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(195);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(155);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(739);
	sleep(100);
	pcspk_play(783);
	sleep(175);
	pcspk_play(246);
	sleep(50);
	pcspk_play(19);
	sleep(100);
	pcspk_play(184);
	sleep(25);
	pcspk_play(195);
	sleep(25);
	pcspk_play(783);
	sleep(150);
	pcspk_play(277);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(880);
	sleep(325);
	pcspk_play(220);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(220);
	sleep(50);
	pcspk_play(261);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(739);
	sleep(200);
	pcspk_play(138);
	sleep(125);
	pcspk_play(293);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(195);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(783);
	sleep(125);
	pcspk_play(739);
	sleep(175);
	pcspk_play(659);
	sleep(175);
	pcspk_play(369);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(293);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(739);
	sleep(100);
	pcspk_play(783);
	sleep(175);
	pcspk_play(38);
	sleep(25);
	pcspk_play(97);
	sleep(125);
	pcspk_play(783);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(783);
	sleep(125);
	pcspk_play(293);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(739);
	sleep(225);
	pcspk_play(123);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(123);
	sleep(50);
	pcspk_play(19);
	sleep(50);
	pcspk_play(246);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(659);
	sleep(225);
	pcspk_play(155);
	sleep(125);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(19);
	sleep(75);
	pcspk_play(246);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(783);
	sleep(150);
	pcspk_play(739);
	sleep(175);
	pcspk_play(659);
	sleep(150);
	pcspk_play(293);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(739);
	sleep(150);
	pcspk_play(783);
	sleep(175);
	pcspk_play(77);
	sleep(25);
	pcspk_play(97);
	sleep(100);
	pcspk_play(277);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(783);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(739);
	sleep(200);
	pcspk_play(123);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(246);
	sleep(25);
	pcspk_play(369);
	sleep(50);
	pcspk_play(19);
	sleep(125);
	pcspk_play(659);
	sleep(200);
	pcspk_play(155);
	sleep(125);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(783);
	sleep(125);
	pcspk_play(739);
	sleep(175);
	pcspk_play(659);
	sleep(150);
	pcspk_play(622);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(587);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(659);
	sleep(175);
	pcspk_play(19);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(50);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(220);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(659);
	sleep(125);
	pcspk_play(277);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(659);
	sleep(350);
	pcspk_play(246);
	sleep(25);
	pcspk_play(123);
	sleep(50);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(19);
	sleep(25);
	pcspk_play(195);
	sleep(25);
	pcspk_play(293);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(138);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_play(220);
	sleep(25);
	pcspk_play(246);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(61);
	sleep(25);
	pcspk_play(195);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(659);
	sleep(100);
	pcspk_play(38);
	sleep(25);
	pcspk_play(246);
	sleep(25);
	pcspk_play(349);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(587);
	sleep(200);
	pcspk_play(523);
	sleep(150);
	pcspk_play(277);
	sleep(25);
	pcspk_play(493);
	sleep(125);
	pcspk_play(184);
	sleep(25);
	pcspk_play(277);
	sleep(25);
	pcspk_play(587);
	sleep(150);
	pcspk_play(554);
	sleep(25);
	pcspk_play(523);
	sleep(150);
	pcspk_play(97);
	sleep(100);
	pcspk_play(123);
	sleep(25);
	pcspk_play(220);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(523);
	sleep(125);
	pcspk_play(220);
	sleep(25);
	pcspk_play(123);
	sleep(50);
	pcspk_play(97);
	sleep(25);
	pcspk_play(123);
	sleep(25);
	pcspk_play(97);
	sleep(25);
	pcspk_play(19);
	sleep(50);
	pcspk_play(493);
	sleep(175);
	pcspk_play(77);
	sleep(125);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(261);
	sleep(25);
	pcspk_play(369);
	sleep(25);
	pcspk_play(77);
	sleep(125);
	pcspk_play(493);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(100);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(19);
	sleep(125);
	pcspk_stop();
}

void pcspk_hc(void)
{
	pcspk_play(123);
	sleep(50);
	pcspk_play(739);
	sleep(150);
	pcspk_play(987);
	sleep(200);
	pcspk_play(493);
	sleep(250);
	pcspk_play(587);
	sleep(200);
	pcspk_play(493);
	sleep(200);
	pcspk_play(739);
	sleep(225);
	pcspk_play(493);
	sleep(200);
	pcspk_play(587);
	sleep(225);
	pcspk_play(987);
	sleep(825);
	pcspk_play(587);
	sleep(450);
	pcspk_play(659);
	sleep(425);
	pcspk_play(1479);
	sleep(25);
	pcspk_play(739);
	sleep(100);
	pcspk_play(466);
	sleep(300);
	pcspk_play(659);
	sleep(225);
	pcspk_play(739);
	sleep(225);
	pcspk_play(659);
	sleep(200);
	pcspk_play(1108);
	sleep(225);
	pcspk_play(739);
	sleep(200);
	pcspk_play(659);
	sleep(200);
	pcspk_play(698);
	sleep(25);
	pcspk_play(739);
	sleep(100);
	pcspk_play(466);
	sleep(1025);
	sleep(575);
	pcspk_play(1760);
	sleep(25);
	pcspk_play(440);
	sleep(400);
	pcspk_play(659);
	sleep(225);
	pcspk_play(880);
	sleep(225);
	pcspk_play(659);
	sleep(200);
	pcspk_play(987);
	sleep(425);
	pcspk_play(880);
	sleep(225);
	pcspk_play(440);
	sleep(425);
	pcspk_play(659);
	sleep(200);
	pcspk_play(698);
	sleep(25);
	pcspk_play(880);
	sleep(200);
	pcspk_play(311);
	sleep(425);
	pcspk_play(659);
	sleep(225);
	pcspk_play(880);
	sleep(200);
	pcspk_play(391);
	sleep(25);
	pcspk_play(659);
	sleep(100);
	pcspk_play(1318);
	sleep(300);
	pcspk_play(739);
	sleep(250);
	pcspk_play(587);
	sleep(200);
	pcspk_play(739);
	sleep(225);
	pcspk_play(587);
	sleep(200);
	pcspk_play(493);
	sleep(225);
	pcspk_play(415);
	sleep(200);
	pcspk_play(987);
	sleep(325);
	pcspk_play(880);
	sleep(25);
	pcspk_play(987);
	sleep(25);
	pcspk_play(880);
	sleep(25);
	pcspk_play(987);
	sleep(25);
	pcspk_play(880);
	sleep(25);
	pcspk_play(987);
	sleep(25);
	pcspk_play(880);
	sleep(1250);
	pcspk_play(783);
	sleep(25);
	pcspk_play(97);
	sleep(75);
	pcspk_play(783);
	sleep(75);
	pcspk_play(97);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_play(19);
	sleep(25);
	pcspk_play(38);
	sleep(25);
	pcspk_stop();
}

void pcspk_acri(void)
{
	pcspk_play(783);
	sleep(50);
	pcspk_play(622);
	sleep(350);
	pcspk_play(261);
	sleep(475);
	pcspk_play(622);
	sleep(650);
	pcspk_play(220);
	sleep(25);
	pcspk_play(195);
	sleep(475);
	pcspk_play(587);
	sleep(375);
	pcspk_play(261);
	sleep(50);
	pcspk_play(698);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(523);
	sleep(25);
	pcspk_play(466);
	sleep(25);
	pcspk_play(587);
	sleep(350);
	pcspk_play(261);
	sleep(125);
	pcspk_play(184);
	sleep(500);
	pcspk_play(523);
	sleep(500);
	pcspk_play(261);
	sleep(25);
	pcspk_play(523);
	sleep(475);
	pcspk_play(493);
	sleep(50);
	pcspk_play(123);
	sleep(450);
	pcspk_play(493);
	sleep(975);
	pcspk_play(391);
	sleep(50);
	pcspk_play(783);
	sleep(200);
	pcspk_play(195);
	sleep(25);
	pcspk_play(783);
	sleep(225);
	pcspk_play(391);
	sleep(25);
	pcspk_play(622);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(622);
	sleep(25);
	pcspk_play(391);
	sleep(50);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(622);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(50);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(50);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(622);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(50);
	pcspk_play(622);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(261);
	sleep(25);
	pcspk_play(391);
	sleep(50);
	pcspk_play(261);
	sleep(75);
	pcspk_play(698);
	sleep(25);
	pcspk_play(311);
	sleep(25);
	pcspk_play(349);
	sleep(150);
	pcspk_play(783);
	sleep(225);
	pcspk_play(195);
	sleep(25);
	pcspk_play(783);
	sleep(225);
	pcspk_play(246);
	sleep(25);
	pcspk_play(349);
	sleep(725);
	pcspk_play(369);
	sleep(50);
	pcspk_play(349);
	sleep(225);
	pcspk_play(391);
	sleep(25);
	pcspk_play(783);
	sleep(225);
	pcspk_play(391);
	sleep(250);
	pcspk_play(783);
	sleep(250);
	pcspk_play(261);
	sleep(325);
	pcspk_play(698);
	sleep(50);
	pcspk_play(261);
	sleep(50);
	pcspk_play(698);
	sleep(50);
	pcspk_play(261);
	sleep(50);
	pcspk_play(698);
	sleep(50);
	pcspk_play(261);
	sleep(50);
	pcspk_play(698);
	sleep(75);
	pcspk_play(261);
	sleep(50);
	pcspk_play(783);
	sleep(500);
	pcspk_play(523);
	sleep(225);
	pcspk_play(391);
	sleep(275);
	pcspk_play(349);
	sleep(25);
	pcspk_play(493);
	sleep(125);
	pcspk_play(349);
	sleep(25);
	pcspk_play(698);
	sleep(150);
	pcspk_play(349);
	sleep(25);
	pcspk_play(622);
	sleep(150);
	pcspk_play(587);
	sleep(250);
	pcspk_play(391);
	sleep(25);
	pcspk_play(246);
	sleep(225);
	pcspk_play(587);
	sleep(25);
	pcspk_play(293);
	sleep(225);
	pcspk_play(783);
	sleep(250);
	pcspk_play(523);
	sleep(500);
	pcspk_play(587);
	sleep(25);
	pcspk_play(155);
	sleep(225);
	pcspk_play(369);
	sleep(25);
	pcspk_play(246);
	sleep(225);
	pcspk_play(293);
	sleep(225);
	pcspk_play(369);
	sleep(25);
	pcspk_play(391);
	sleep(25);
	pcspk_play(293);
	sleep(225);
	pcspk_play(523);
	sleep(25);
	pcspk_stop();
}
