#include <stdio.h>
#include <iostream>
#include <string>
#include "frame_of_reference.h"
#include "compress_data.h"

#define SUCCESS 0
#define ERROR 1
#define PARAMETERS 5

int handle_command(char const *argv[]) {
    int n = std::stoi(argv[1], nullptr);
    int t = std::stoi(argv[2], nullptr);
    int q = std::stoi(argv[3], nullptr);
    std::string infile = std::string(argv[4]);
    std::string outfile = std::string(argv[5]);
    struct CompressData cd;
    cd.block_size = n;
    cd.threads = t;
    cd.queue_limit = q;

    try {
        FrameOfReference frmOfRef(infile, outfile, cd);
        frmOfRef.start();
        return SUCCESS;
    } catch(const char* error_msg) {
        std::cout << error_msg << "\n";
        return ERROR;
    }
}

int main(int argc, char const *argv[]) {
    if (argc < PARAMETERS + 1 || argc > PARAMETERS + 1) {
        std::cout << "Formato: ./tp <N> <T> <Q> <infile> <outfile>" << "\n";
    }

    return handle_command(argv);
}
