// http://man7.org/linux/man-pages/man2/socket.2.html

#include <sys/socket.h> // socket

#include <unistd.h> // write

#include <sys/un.h> // sockaddr_un

// #include <stdio.h>
// #include <stdlib.h>

#include <string.h> // strncopy

int main(int argc, char **argv)
{
    int fd;                  //file descriptor
    struct sockaddr_un addr; // Socket address, set to
    addr.sun_family = AF_UNIX;

    char *socket_path = "/tmp/mysocket";
    // Do: addr.sun_path = AF_UNIX + socket_path
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    // Create socket fd, connect to it using address
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    // sockets are files, so you can just write to it
    write(fd, "write-hello\n", 12);

    // alternatively, you can use send(), which allows for additional flags
    // NOTE: write() is equivalent to send() with a flags parameter of 0.
    // Other values for the flags parameter change the behaviour of recv().
    // Similarly, read() is equivalent to recv() with flags == 0.
    send(fd, "send-hello\n", 11, 0);

    // Make sure we fsync so data is fully written before program ends and socket is closed
    // This avoids "broken pipe" errors on the server-side.
    fsync(fd);
}