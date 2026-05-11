#include <sys/socket.h>
#include <sys/event.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(9001),
        .sin_addr.s_addr = INADDR_ANY};

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 10);

    int kq = kqueue();

    struct kevent evSet;
    EV_SET(&evSet, server_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kevent(kq, &evSet, 1, NULL, 0, NULL);

    printf("Server listening on 9001\n");

    while (1)
    {
        struct kevent ev;
        int nev = kevent(kq, NULL, 0, &ev, 1, NULL);

        if (nev > 0)
        {
            if (ev.ident == server_fd)
            {
                // New client
                int client_fd = accept(server_fd, NULL, NULL);
                printf("New client %d\n", client_fd);

                EV_SET(&evSet, client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                kevent(kq, &evSet, 1, NULL, 0, NULL);
            }
            else
            {
                char buf[1024];
                int n = read(ev.ident, buf, sizeof(buf));
                if (n <= 0)
                {
                    printf("Client %lu disconnected\n", ev.ident);
                    close(ev.ident);
                }
                else
                {
                    write(ev.ident, buf, n); // echo
                }
            }
        }
    }
}