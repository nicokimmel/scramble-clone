#ifndef SCRAMBLE_BYTES_H
#define SCRAMBLE_BYTES_H

/**
 * @brief Liest ein Byte aus einem Buffer aus und wandelt es in einen Integer
 * @details Deklariert einen kleinen Zwischenbuffer um aus dem größeren
 * 			Buffer auszulesen. Anschließend wird der Buffer als 16 Bit
 * 			Integer reinterpretiert.
 * 
 * @param buffer Buffer aus dem ausgelesen werden soll
 * @param offset Offset innerhalb des Buffers
 * @return Auszulesener 16 Bit Integer
 */
inline int16_t byte_to_int16(char* buffer, int offset) {
    auto byte = std::make_shared<char[]>(4);
    byte[0] = buffer[offset];
    byte[1] = buffer[offset + 1];
    byte[2] = buffer[offset + 2];
    byte[3] = buffer[offset + 3];
    return *std::reinterpret_pointer_cast<int16_t>(byte).get();
}

/**
 * @brief Liest ein Byte aus einem Buffer aus und wandelt es in einen Integer
 * @details Deklariert einen kleinen Zwischenbuffer um aus dem größeren
 * 			Buffer auszulesen. Anschließend wird der Buffer als 8 Bit
 * 			Integer reinterpretiert.
 * 
 * @param buffer Buffer aus dem ausgelesen werden soll
 * @param offset Offset innerhalb des Buffers
 * @return Auszulesener 8 Bit Integer
 */
inline uint8_t byte_to_uint8(char* buffer, int offset) {
    auto byte = std::make_shared<char[]>(1);
    byte[0] = buffer[offset];
    return *std::reinterpret_pointer_cast<u_int8_t>(byte).get();
}

#endif //SCRAMBLE_BYTES_H