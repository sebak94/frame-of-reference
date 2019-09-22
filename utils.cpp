#include <stdint.h>
#include <cmath>

uint8_t number_of_bits(uint32_t value) {
    return value != 0 ? (uint8_t)ceil(log(value) / log(2)) : 0;
}

uint32_t minimum(uint32_t valueA, uint32_t valueB) {
    return valueA < valueB ? valueA : valueB;
}

uint32_t maximum(uint32_t valueA, uint32_t valueB) {
    return valueA > valueB ? valueA : valueB;
}

uint32_t minimum_in_array(uint32_t *array, size_t length) {
    uint32_t min = array[0];

    for (size_t i = 0; i < length; i++) {
        uint32_t value = array[i];
        min = minimum(min, value);
    }

    return min;
}
