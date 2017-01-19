// this file is called libmy.so because all gcc assumes all libs start with 'lib'
#include <stdio.h>

void print_hello() {
    printf("Haha, hijacked print_hello!");
}