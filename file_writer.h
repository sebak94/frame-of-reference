#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__

#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>

// Wrapper de fstream para escribir en el archivo
class FileWriter {
    private:
    std::fstream fs;

    public:
    explicit FileWriter(const std::string filename);
    // Escribe block de tamaño size en el archivo abierto
    void write(const char *block, size_t size);
    // Devuelve si hubo errores en la última operación
    int error();
    ~FileWriter();
};

#endif
