/*
 *
 * Carina
 * Header for Framebuffer Driver
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

#ifndef __FB_H__
#define __FB_H__

#include <stdlib.h>

#define FB_CNT			4

u8 fb_focus;

u16 *fb_buffer;
u16 fb_buffers[FB_CNT];

u16 fb_x[FB_CNT];
u16 fb_y[FB_CNT];

u8 fb_fgcolor;
u8 fb_bgcolor;

void fb_init(const u8 fb);

void fb_cur_set(void);
void fb_cur_style(const u8 style);

void fb_clr(void);
void fb_scrl_dwn(void);

#endif
