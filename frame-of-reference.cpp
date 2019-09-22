#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include "compressor.h"

#define SUCCESS 0
#define ERROR 1
#define PARAMETERS 5
#define MAX_FILENAME_LENGTH 30

void handle_command(char const *argv[]);

int main(int argc, char const *argv[]) {
    if (argc < PARAMETERS + 1 || argc > PARAMETERS + 1) {
        std::cout << "Formato: ./tp <N> <T> <Q> <infile> <outfile>" << "\n";
    }

    handle_command(argv);

    return SUCCESS;
}

void handle_command(char const *argv[]) {
    int n = std::stoi(argv[1], nullptr);
    // int t = std::stoi(argv[2], nullptr);
    // int q = std::stoi(argv[3], nullptr);
    std::string infile = std::string(argv[4]);
    std::string outfile = std::string(argv[5]);

    try {
        Compressor comp(infile, outfile, n);
        comp.start();
    } catch(const char* error_msg) {
        std::cout << error_msg << "\n";
    }
}
