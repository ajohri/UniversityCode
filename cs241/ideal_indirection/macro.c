#define GENERAL__GET_BITS_FROM_U8(source,lsb,msb) \
    ((uint8_t)((source) & \
        ((uint8_t)(((uint8_t)(0xFF >> ((uint8_t)(7-((uint8_t)(msb) & 7))))) & \
             ((uint8_t)(0xFF << ((uint8_t)(lsb) & 7)))))))

#define GENERAL__GET_BITS_FROM_U16(source,lsb,msb) \
    ((uint16_t)((source) & \
        ((uint16_t)(((uint16_t)(0xFFFF >> ((uint8_t)(15-((uint8_t)(msb) & 15))))) & \
            ((uint16_t)(0xFFFF << ((uint8_t)(lsb) & 15)))))))

#define GENERAL__GET_BITS_FROM_U32(source,lsb,msb) \
    ((uint32_t)((source) & \
        ((uint32_t)(((uint32_t)(0xFFFFFFFF >> ((uint8_t)(31-((uint8_t)(msb) & 31))))) & \
            ((uint32_t)(0xFFFFFFFF << ((uint8_t)(lsb) & 31)))))))