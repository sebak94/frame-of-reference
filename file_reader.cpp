#include "file_reader.h"
#include "lock.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

FileReader::FileReader(const std::string filename) {
    if (filename == "-") {
        fs.basic_ios<char>::rdbuf(std::cin.rdbuf());
    } else {
        fs.open(filename, std::ios_base::in | std::ios_base::binary);
        if (fs.fail()) throw "fopen failed";
    }
}

size_t FileReader::seekg_read_and_gcount(char *block, size_t size, size_t pos) {
    Lock l(m);
    fs.seekg(pos, fs.beg);
    fs.read(block, size);
    return fs.gcount();
}

size_t FileReader::glength() {
    Lock l(m);
    fs.seekg(0, fs.end);
    int length = fs.tellg();
    fs.seekg(0, fs.beg);
    return length;
}

int FileReader::error() {
    Lock l(m);
    return fs.fail() || fs.bad();
}

FileReader::~FileReader() {
    fs.close();   
}
