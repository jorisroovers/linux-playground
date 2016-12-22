#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    for (;;) {
        // allocate 1000 bytes, we leak this memory here but who cares, it's an example :p
        malloc(1000);
        sleep(1);
    }
}
