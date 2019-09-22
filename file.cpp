#include "file.h"
#include <stdint.h>
#include <vector>

File::File(const std::string filename, std::ios_base::openmode mode) {
    fs.open(filename, mode);
    if (fs.fail()) throw "fopen failed";
}

void File::read(char *block, size_t size) {
    fs.read(block, size);
}

void File::write(const char *block, size_t size) {
    fs.write(block, size);
}

int File::glength() {
    fs.seekg (0, fs.end);
    int length = fs.tellg();
    fs.seekg (0, fs.beg);
    return length;
}

int File::gcount() {
    return fs.gcount();
}

int File::error() {
    return fs.fail() || fs.bad();
}

int File::eof() {
    return fs.eof();
}

File::~File() {
    fs.close();   
}
