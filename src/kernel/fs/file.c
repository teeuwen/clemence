/*
 *
 * Elarix
 * src/kernel/fs/file.c
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

#include <errno.h>
#include <fs.h>
#include <limits.h>
#include <proc.h>

#include <stdlib.h>

int file_cnt = 0;

struct file *file_alloc(struct dirent *dep)
{
	struct file *fp;

	if (file_cnt + 1 > FD_MAX)
		return NULL;

	fp = kmalloc(sizeof(struct file));
	if (!fp)
		return NULL;

	fp->mode = 0;
	fp->off = 0;

	fp->refs = 1;

	fp->dep = dep;

	fp->op = dep->ip->fop;

	file_cnt++;

	return fp;
}

void file_dealloc(struct file *fp)
{
	if (!fp)
		return;

	kfree(fp);

	file_cnt--;
}

struct file *file_get(int fd)
{
	return cproc->fd[fd];
}