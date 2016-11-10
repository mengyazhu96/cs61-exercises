#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Fork a child, who reads from my stdout.
// Then, read from standard in.
// Output the first thing read to stderr
// Then write everything after it to standard out, removing anything that
// is a multiple of that first value.

int main(int argc, char *argv[]) {
	(void)argc;

	int val;
	int num;
	int pipefd[2];

	if (pipe(pipefd) != 0)
		exit(1);

	pid_t child = fork();

	// This is the child.
	if (child == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
	} else if (child > 0) {  // This is the parent.
		// Close the read end of the pipe.
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execvp(argv[0], argv);
	}

	// Read first value and output to stderr
	if (scanf("%d ", &val) != 1)
		exit(1);
	fprintf(stderr, "%d ", val);

	// TODO: Read values from your standard input and write them to
	// your standard output if they are not a multiple of val.
	while (scanf("%d ", &num) == 1)
		if (num % val != 0)
			fprintf(stdout, "%d ", num);
}
