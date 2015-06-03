/* Copyright (c) 2013-2015, Drew Thoreson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

#include <dirent.h>
#include <unistd.h>
#include "error.h"

#define NR_DIRS 8

static DIR dirs[NR_DIRS];

static inline DIR *get_free_dir(void)
{
	int i;
	for (i = 0; i < NR_DIRS; i++)
		if (!dirs[i].fd)
			return &dirs[i];
	return NULL;
}

DIR *opendir(const char *pathname)
{
	int rc;
	DIR *dir;

	if ((dir = get_free_dir()) == NULL)
		return_nullerr(-ENOMEM);

	if ((rc = open(pathname, 0)) < 0)
		return_nullerr(rc);

	dir->fd = rc;
	dir->dirent.d_off = 0;
	return dir;
}

DIR *fdopendir(int fd)
{
	DIR *dir;

	if ((dir = get_free_dir()) == NULL)
		return_nullerr(-ENOMEM);

	dir->fd = fd;
	dir->dirent.d_off = 0;
	return dir;
}
