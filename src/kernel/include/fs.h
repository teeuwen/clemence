/*
 *
 * Elarix
 * src/kernel/include/fs.h
 *
 * Copyright (C) 2016 - 2017 Bastiaan Teeuwen <bastiaan@mkcl.nl>
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

#ifndef _FS_H
#define _FS_H

/* BEGIN fs.h */

#include <limits.h>
#include <list.h>

/* Superblock flags */
#define SF_KEEP		1	/* Don't remove from cache */

#if 0
/* Inode flags */
#define IF_RO		1	/* Read only */
#define IF_AO		2	/* Append only */
#define IF_IMMUTABLE	4	/* Immutable */
#define IF_NOATIME	8	/* Do not update access time */
#define IF_SYNC	16	/* Synchronous updates */
#endif

/* File mode */
#define FM_FTM		0170000
#define FM_LNK		0120000	/* Symbolic link */
#define FM_REG		0100000	/* Regular file */
#define FM_BLK		0060000	/* Block device */
#define FM_DIR		0040000	/* Directory */
#define FM_CHR		0020000	/* Character device */
#define FM_FIFO		0010000	/* Pipe */

#define FM_SUID		0004000	/* Set UID on execution */
#define FM_SGID		0002000	/* Set GID on execution */

#define FM_UM		0000700
#define FM_UR		0000400	/* Owner read */
#define FM_UW		0000200	/* Owner write */
#define FM_UE		0000100	/* Owner execute */

#define FM_GM		0000070
#define FM_GR		0000040	/* Group read */
#define FM_GW		0000020	/* Group write */
#define FM_GE		0000010	/* Group execute */

#define FM_OM		0000007
#define FM_OR		0000004	/* Other read */
#define FM_OW		0000002	/* Other write */
#define FM_OE		0000001	/* Other execute */

struct superblock {
	struct list_head l;

	dev_t	dev;			/* Device identifier */
	char	name[NAME_MAX + 1];	/* Device name */
	u8	flags;			/* Superblock flags */

	u64	blocks;			/* First block */
	u16	block_size;		/* Block size */
	/* u64	size_max; */		/* Max. file size */

	void *device;			/* Device specific superblock (opt.) */

	struct inode *root;		/* Root dirent */
	struct list_head il;		/* Inodes */

	struct sb_ops *op;
};

struct inode {
	struct list_head l;

	ino_t	inum;			/* Inode number */

	int	refs;			/* Reference count */
	link_t	links;			/* Link count */

	dev_t	dev;			/* Device ID (only for devices) */
	uid_t	uid;			/* User ID */
	gid_t	gid;			/* Group ID */

	time_t	atime;			/* Access time */
	time_t	ctime;			/* Change time */
	time_t	mtime;			/* Modification time */

	off_t	size;			/* File size in bytes */

	struct superblock	*sp;	/* Associated superblock */
	struct list_head	del;	/* List of children (only for dirs.) */

	struct inode_ops	*op;
	struct file_ops		*fop;
};

struct dirent {
	struct list_head l;

	char	name[NAME_MAX + 1];	/* File name */
	mode_t	mode;			/* File mode */

	int	refs;			/* Reference count */

	struct inode	*ip;		/* Associated inode pointer */
	struct dirent	*dp;		/* Associated directory pointer */
};

struct usr_dirent {
	ino_t	inum;			/* Inode number */

	char	name[NAME_MAX + 1];	/* File name */
};

struct file {
	mode_t	mode;			/* File mode */

	int	refs;			/* Reference count */

	off_t	off;			/* Current offset */

	struct dirent	*dep;		/* Associated directory entry pointer */
};

struct sb_ops {
	/* Allocate a memory inode: sp */
	struct inode *(*inode_alloc) (struct superblock *);
	/* Deallocate a memory inode: ip */
	void (*inode_dealloc) (struct inode *);
	/* Write an inode to disk: ip */
	int (*inode_write) (struct inode *);
	/* Delete an inode from disk: ip */
	void (*inode_delete) (struct inode *);
	/* TODO (sync) */
};

struct inode_ops {
	/* Create a file: dp, dep, mode */
	int (*create) (struct inode *, struct dirent *, mode_t);
	/* Create a hard link: dp, dep, name */
	int (*link) (struct inode *, struct dirent *, struct dirent *);
	/* Create a symbolic link: dp, dep, name */
	int (*symlink) (struct inode *, struct dirent *, const char *);
	/* Delete a link: dp, dep */
	int (*rmlink) (struct inode *, struct dirent *);
	/* Create a directory: dp, dep, mode */
	int (*mkdir) (struct inode *, struct dirent *, mode_t);
	/* Delete a directory: dp, dep */
	int (*rmdir) (struct inode *, struct dirent *);
	/* Create a special file: dp, dep, mode, dev */
	int (*mknod) (struct inode *, struct dirent *, mode_t, dev_t);
	/* Move a dirent: odp, odep, dp, dep */
	int (*move) (struct inode *, struct dirent *,
			struct inode *, struct dirent *);
	/* Look up a directory entry: dp, name */
	struct dirent *(*lookup) (struct dirent *, const char *);
	/* Read directory: dp */
	int (*readdir) (struct dirent *);
	/* TODO (perm), (setattr / getattr), (readlink) */
};

struct dirent_ops {
	/* Close the directory entry: dp */
	int (*close) (struct dirent *);
};

struct file_ops {
	/* Create a new file object: ip, &fp */
	int (*open) (struct inode *, struct file *);
	/* Delete a file object: ip, fp */
	int (*close) (struct inode *, struct file *);
	/* Read n bytes at off from fp into buf: fp, buf, off, n */
	int (*read) (struct file *, char *, off_t, size_t);
	/* Write n bytes from buf into fp at off: fp, buf, off, n */
	int (*write) (struct file *, const char *, off_t, size_t);
	/* Read next directory: fp, TODO */
	int (*readdir) (struct file *, struct usr_dirent *);
	/* I/O control: fp, cmd, arg */
	int (*ioctl) (struct file *, unsigned int, unsigned long);
	/* TODO (sync / fsync) */
};

struct fs_driver {
	struct list_head l;

	const char *name;

	/* Read the superblock: sp, data */
	struct inode *(*read_sb) (struct superblock *);
};

extern struct superblock *root_sb;
extern struct dirent root_dep;

struct file *fs_open(const char *path, int flags, mode_t mode);
int fs_close(struct file *fp);
int fs_read(struct file *fp, char *buf, off_t off, size_t n);
int fs_write(struct file *fp, const char *buf, off_t off, size_t n);
int fs_readdir(struct file *fp, struct usr_dirent *udep);

int fs_reg(struct fs_driver *driver);
void fs_unreg(struct fs_driver *driver);

struct superblock *sb_alloc(struct fs_driver *driver);

struct inode *inode_alloc(struct superblock *sp);
struct inode *inode_get(struct superblock *sp, ino_t inum);
void inode_put(struct inode *ip);

struct dirent *dirent_alloc(struct dirent *dp, const char *name);
struct dirent *dirent_get(const char *path);
struct usr_dirent *usr_dirent_get(struct file *fp);
void dirent_put(struct dirent *dep);

struct file *file_alloc(struct dirent *dep);
void file_put(struct file *fp);

/* XXX TMP XXX */
int sv_mkdir(const char *path, mode_t mode);
int sys_mount(const char *device, const char *path, const char *fs);
int sys_chdir(const char *path);
int sys_cwdir(char *path);
int sys_mkdir(const char *path, mode_t mode);
/* XXX END TMP XXX */

/* END fs.h */


/* BEGIN dev.h */

#define MAJOR_ZERO	0
#define MAJOR_MEM	1
#define MAJOR_CON	2
#define MAJOR_KBD	3
#define MAJOR_MOUSE	4
#define MAJOR_DISK	5
#define MAJOR_OPTICAL	6
#define MAJOR_SOUND	7
#define MAJOR_MISC	255

struct device {
	const char	*name;
	struct file_ops	*op;
};

int dev_reg(u8 major, const char *name, struct file_ops *op);
void dev_unreg(u8 major);

int dev_init(dev_t dev);

/* END dev.h */

#if 0
/* BEGIN mount.h */

struct mountp {
	struct mountp	*pp;	/* Parent fs */

	struct superblock *sp;	/* Superblock */

	char *name;		/* Device path or name */
};

/* END mount.h */
#endif

#endif
