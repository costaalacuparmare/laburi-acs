// SPDX-License-Identifier: BSD-3-Clause

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "utils.h"

#define READ		0
#define WRITE		1

/**
 * Internal change-directory command.
 */
static int shell_cd(word_t *dir)
{
	if (dir == NULL || dir->string == NULL)
		return 1;
	return chdir(dir->string);
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	return SHELL_EXIT;
}

/**
 * Get the arguments list for a simple command.
 */
static int shell_pwd(void)
{
	char *cwd = getcwd(NULL, 0);

	if (cwd == NULL) {
		perror("getcwd() error");
		return 1;
	}
	printf("%s\n", cwd);
	free(cwd);
	return 0;
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	// Sanity checks
	if (s == NULL)
		return 0;

	// Internal commands
	if (strcmp(s->verb->string, "pwd") == 0)
		return shell_pwd();
	if (strcmp(s->verb->string, "exit") == 0 || strcmp(s->verb->string, "quit") == 0)
		return shell_exit();
	if (strcmp(s->verb->string, "cd") == 0) {
		if (s->verb->string == NULL || s->verb->next_part != NULL) {
			perror("Invalid command");
			return 0;
		}
		return shell_cd(s->params);
	}

	// Environment variable assignment
	if (s->verb->next_part != NULL && !strcmp(s->verb->next_part->string, "=")) {
		char *value = get_word(s->verb->next_part->next_part);
		int ret_env = setenv(s->verb->string, value, 1);

		free(value);
		return ret_env;
	}

	// External commands
	pid_t pid;
	pid_t ret_wait;
	int status = -1;
	int argc;
	char **argv;

	pid = fork();
	switch (pid) {
	case -1:
		/* Error */
		DIE(1, "fork");
		break;
	case 0:
		/* Child process */
		argv = get_argv(s, &argc);
		execvp(*argv, argv);
		exit(127);
		break;
	default:
		/* Parent process */
		ret_wait = waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 127)
			fprintf(stderr, "Execution failed for '%s'\n", s->verb->string);
		DIE(ret_wait < 0, "waitpid");
	}
	return status;
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool run_in_parallel(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	pid_t pid;
	pid_t ret_wait;
	int status;

	pid = fork();
	switch (pid) {
	case -1:
		/* Error */
		DIE(1, "fork");
		break;
	case 0:
		/* Child process */
		exit(parse_command(cmd1, level + 1, father));
	default:
		/* Parent process */
		status = parse_command(cmd2, level + 1, father);
		ret_wait = waitpid(pid, &status, 0);
		DIE(ret_wait < 0, "waitpid");
	}
	return status;
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2).
 */
static int run_on_pipe(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	int fd[2];
	pid_t pid;
	int status;
	int ret = pipe(fd);

	DIE(ret == -1, "error on pipe");
	pid = fork();
	if (pid == -1) {
		/* Error */
		perror("fork() error");
		return 0;
	}
	if (pid == 0) {
		/* Child process */
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(parse_command(cmd1, level + 1, father));
	}
	/* Parent process */
	int old_fd_in = dup(STDIN_FILENO);

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	ret = parse_command(cmd2, level + 1, father);
	waitpid(pid, &status, 0);
	close(fd[0]);
	dup2(old_fd_in, STDIN_FILENO);
	close(old_fd_in);
	return ret;
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father)
{
	// Sanity checks
	if (c == NULL)
		return 0;

	int ret;

	if (c->op == OP_NONE) {
		int old_fd_in = -1;
		int old_fd_out = -1;
		int old_fd_err = -1;

		// < : redirection to stdin
		if (c->scmd->in != NULL) {
			old_fd_in = dup(STDIN_FILENO);
			char *input_path = NULL;

			input_path = get_word(c->scmd->in);
			int fd_in = open(input_path, O_RDONLY, 0644);

			DIE(fd_in == -1, "open stdin");
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			free(input_path);
		}

		// >, >> : redirection to stdout
		if (c->scmd->out != NULL) {
			old_fd_out = dup(STDOUT_FILENO);
			char *output_path = NULL;

			output_path = get_word(c->scmd->out);
			int fd_out = -1;

			if (c->scmd->io_flags & IO_OUT_APPEND)
				fd_out = open(output_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd_out = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			DIE(fd_out == -1, "open stdout");
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			free(output_path);
		}

		// 2> : redirection to stderr
		if (c->scmd->err != NULL) {
			old_fd_err = dup(STDERR_FILENO);
			if (c->scmd->err == c->scmd->out) {
				dup2(STDOUT_FILENO, STDERR_FILENO);
			} else {
				char *error_path = NULL;

				error_path = get_word(c->scmd->err);
				int fd_err = -1;

				if (c->scmd->io_flags & IO_ERR_APPEND)
					fd_err = open(error_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd_err = open(error_path, O_WRONLY | O_CREAT | O_TRUNC,  0644);
				DIE(fd_err == -1, "open stderr");
				dup2(fd_err, STDERR_FILENO);
				close(fd_err);
				free(error_path);
			}
		}
		ret = parse_simple(c->scmd, level, father);
		if (old_fd_in != -1)
			dup2(old_fd_in, STDIN_FILENO);
		if (old_fd_out != -1)
			dup2(old_fd_out, STDOUT_FILENO);
		if (old_fd_err != -1)
			dup2(old_fd_err, STDERR_FILENO);
		return ret;
	}
	switch (c->op) {
	case OP_SEQUENTIAL:
		parse_command(c->cmd1, level, father);
		parse_command(c->cmd2, level, father);
		break;

	case OP_PARALLEL:
		ret = run_in_parallel(c->cmd1, c->cmd2, level, father);
		break;

	case OP_CONDITIONAL_NZERO:
		ret = parse_command(c->cmd1, level, father);
		if (ret != 0)
			ret = parse_command(c->cmd2, level, father);
		break;

	case OP_CONDITIONAL_ZERO:
		ret = parse_command(c->cmd1, level, father);
		if (ret == 0)
			ret = parse_command(c->cmd2, level, father);
		break;

	case OP_PIPE:
		ret = run_on_pipe(c->cmd1, c->cmd2, level, father);
		break;

	default:
		return SHELL_EXIT;
	}
	return ret;
}
