#ifndef __DATA_WRITER_H__
#define __DATA_WRITER_H__

#include "thread.h"
#include "file_writer.h"
#include "block.h"
#include "blocking_queue.h"
#include "vector"
#include <bitset>

#define BYTE 8

// Clase que desencola bloques de las colas y las guarda en disco
// de forma ordenada
class DataWriter {
    private:
    FileWriter *fw;
    std::vector<BlockingQueue*> queues;

    void write_byte(std::bitset<BYTE> &byte);

    public:
    explicit DataWriter(FileWriter *rw);
    // Loop principal. Desencola y llama a write hasta que el bloque sea nulo
    void start();
    // Escribe en el archivo los datos del bloque comprimido
    void write(Block &b);
    // Agrega una cola bloqueante al vector
    void add_queue(BlockingQueue *queue);
    ~DataWriter();
};

#endif
