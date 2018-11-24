// http://man7.org/linux/man-pages/man2/socket.2.html

#include <sys/types.h>
#include <sys/socket.h>


int main(int argc, char **argv) {

    // TODO: this isn't finished


    int socket(int domain, int type, int protocol);

    // Create a TCP socket
    socket(AF_INET /* IP */, SOCK_STREAM /* TCP */, 0);

    // If you want to raw device access, you should use AF_PACKET with SOCK_RAW


}