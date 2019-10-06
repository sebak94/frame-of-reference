#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__

#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>

class FileWriter {
    private:
    std::fstream fs;
    std::mutex m;

    public:
    explicit FileWriter(const std::string filename);
    void write(const char *block, size_t size);
    int error();
    ~FileWriter();
};

#endif
