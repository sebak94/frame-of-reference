#include "file_writer.h"
#include "lock.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

FileWriter::FileWriter(const std::string filename) {
    if (filename == "-") {
        fs.basic_ios<char>::rdbuf(std::cout.rdbuf());
    } else {
        fs.open(filename, std::ios_base::out | std::ios_base::binary);
        if (fs.fail()) throw "fopen failed";
    }
}

void FileWriter::write(const char *block, size_t size) {
    fs.write(block, size);
}

int FileWriter::error() {
    return fs.fail() || fs.bad();
}

FileWriter::~FileWriter() {
    fs.close();   
}
