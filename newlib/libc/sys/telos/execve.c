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

#include <stddef.h>
#include <string.h>
#include <telos/exec.h>
#include <telos/syscall.h>
#include "error.h"

static int do_execve(const char *pathname, char *const argv[],
		char *const envp[], size_t argc, size_t envc)
{
	size_t i;
	struct _Telos_string s_argv[argc];
	struct _Telos_string s_envp[envc];
	struct exec_args e_args = {
		.pathname = {
			.str = pathname,
			.len = strlen(pathname),
		},
		.argv = s_argv,
		.envp = s_envp,
		.argc = argc,
		.envc = envc,
	};

	for (i = 0; i < argc; i++) {
		s_argv[i].str = argv[i];
		s_argv[i].len = strlen(argv[i]);
	}

	for (i = 0; i < envc; i++) {
		s_envp[i].str = envp[i];
		s_envp[i].len = strlen(envp[i]);
	}

	return syscall1(SYS_EXECVE, &e_args);
}

int execve(char *pathname, char **argv, char **envp)
{
	int error;
	size_t argc, envc;
	for (argc = 0; argv[argc]; argc++);
	for (envc = 0; envp[envc]; envc++);
	error = do_execve(pathname, argv, envp, argc, envc);
	if (error < 0)
		return_error(error);
	/* should be unreachable... */
	return 0;
}
