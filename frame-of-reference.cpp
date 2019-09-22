#include <stdio.h>
#include <stdint.h>
#include "compressor.h"

#define SUCCESS 0
#define ERROR 1
#define NUMBER_BYTES 3

int main(int argc, char const *argv[]) {
    try {
        Compressor comp("zeroblk", "zeroblk3-s.out", NUMBER_BYTES);
        comp.start();
    } catch (const char* error_msg) {
        printf("%s\n", error_msg);
    }

    return SUCCESS;
}
