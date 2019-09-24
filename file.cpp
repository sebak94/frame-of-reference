#include "file.h"
#include "lock.h"
#include <stdint.h>
#include <vector>
#include <string>

File::File(const std::string filename, std::ios_base::openmode mode) {
    fs.open(filename, mode);
    if (fs.fail()) throw "fopen failed";
}

size_t File::seekg_read_and_gcount(char *block, size_t size, size_t pos) {
    Lock l(m);
    fs.seekg(pos, fs.beg);
    fs.read(block, size);
    return fs.gcount();
}

void File::write(const char *block, size_t size) {
    Lock l(m);
    fs.write(block, size);
}

size_t File::glength() {
    Lock l(m);
    fs.seekg(0, fs.end);
    int length = fs.tellg();
    fs.seekg(0, fs.beg);
    return length;
}

int File::error() {
    Lock l(m);
    return fs.fail() || fs.bad();
}

File::~File() {
    fs.close();   
}
