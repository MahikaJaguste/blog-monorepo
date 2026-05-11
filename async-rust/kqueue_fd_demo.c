#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pipefd[2];

void *writer_thread(void *arg)
{
    sleep(2); // give kevent time to block
    const char *msg = "hello\n";
    write(pipefd[1], msg, strlen(msg));
    printf("Writer: wrote to pipe (FD now readable)\n");
    return NULL;
}

int main()
{
    // Create pipe (FD readiness source)
    if (pipe(pipefd) != 0)
    {
        perror("pipe");
        exit(1);
    }

    // Create kqueue
    int kq = kqueue();
    if (kq == -1)
    {
        perror("kqueue");
        exit(1);
    }

    // Register interest in READ events on pipe read-end
    struct kevent ev;
    EV_SET(&ev,
           pipefd[0],   // ident = fd
           EVFILT_READ, // filter
           EV_ADD,      // flags
           0,
           0,
           NULL);

    if (kevent(kq, &ev, 1, NULL, 0, NULL) == -1)
    {
        perror("kevent register");
        exit(1);
    }

    // Start writer thread
    pthread_t t;
    pthread_create(&t, NULL, writer_thread, NULL);

    printf("Main: blocking in kevent() waiting for FD readiness...\n");

    // This blocks -> thread is put on a wait queue in kernel
    // until the pipe becomes readable
    struct kevent triggered;
    int nev = kevent(kq, NULL, 0, &triggered, 1, NULL);
    if (nev == -1)
    {
        perror("kevent wait");
        exit(1);
    }

    printf("Main: kevent woke up! fd=%lu readable bytes=%ld\n",
           triggered.ident,
           triggered.data);

    // Consume the data
    char buf[32];
    read(pipefd[0], buf, sizeof(buf));

    pthread_join(t, NULL);
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}