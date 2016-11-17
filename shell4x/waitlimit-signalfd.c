#include "helpers.h"

void signal_handler(int signal) {
    (void) signal;
}

int main(void) {
    fprintf(stderr, "%.6f: parent: Hello from pid %d\n", 0.0, getpid());

    // GOAL: Use `signalfd`, rather than a signal-pipe (as in the
    // current code), to reliably detect a SIGCHLD signal. Your
    // eventual code should NOT have a `signalpipe`. See `man signalfd`.
    int r;
    int sfd;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sfd = signalfd(-1, &mask, 0);
    r = handle_signal(SIGCHLD, signal_handler);
    assert(r >= 0);


    // Start a child
    double start_time = timestamp();
    pid_t p1 = fork();
    assert(p1 >= 0);
    if (p1 == 0) {
        usleep(500000);
        fprintf(stderr, "%.6f: child: Goodbye from pid %d\n",
                timestamp() - start_time, getpid());
        exit(0);
    }

    // Wait for 0.75 sec, or until a byte is written to `sfd`,
    // whichever happens first
    struct timeval timeout = { 0, 750000 };
    fd_set fds;
    FD_SET(sfd, &fds);
    select(sfd, &fds, NULL, NULL, &timeout);

    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
    assert(exited_pid == 0 || exited_pid == p1);

    double elapsed = timestamp() - start_time;
    if (exited_pid == 0)
        fprintf(stderr, "%.6f: parent: Child timed out\n", elapsed);
    else if (WIFEXITED(status))
        fprintf(stderr, "%.6f: parent: Child exited with status %d\n",
                elapsed, WEXITSTATUS(status));
    else
        fprintf(stderr, "%.6f: parent: Child exited abnormally [%x]\n",
                elapsed, status);
}
