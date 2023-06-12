#include "simd_delta.hpp"

#include "simd_util.hpp"

void decompress_scalar(const int8_t* __restrict input, uint32_t start_value, size_t input_size, uint32_t* __restrict output) {
    uint32_t current = start_value;
    for (size_t i = 0; i < input_size; ++i) {
        current += static_cast<uint32_t>(input[i]);
        output[i] = current;
    }
}


size_t scan_scalar(uint32_t predicate_low, uint32_t predicate_high, int8_t* __restrict input,
                   uint32_t start_value, size_t input_size, uint32_t* __restrict output) {
    uint32_t current = start_value;
    size_t count = 0;
    for (size_t i = 0; i < input_size; ++i) {
        current += static_cast<uint32_t>(input[i]);
        if (current >= predicate_low && current <= predicate_high) {
            output[count] = i;
            ++count;
        }
    }
    return count;
}