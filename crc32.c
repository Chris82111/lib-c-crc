/*---------------------------------------------------------------------*
 *  private: include files
 *---------------------------------------------------------------------*/

#include "crc32.h"


/*---------------------------------------------------------------------*
 *  private: definitions
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  private: typedefs
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  private: variables
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  public:  variables
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  private: function prototypes
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  private: functions
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  public:  functions
 *---------------------------------------------------------------------*/
 
uint32_t get_most_significant_bit(uint32_t data)
{
    data |= (data >> 0x01);
    data |= (data >> 0x02);
    data |= (data >> 0x04);
    data |= (data >> 0x08);
    data |= (data >> 0x10);
    #if false
    return (x & ~(x >> 1));
    #else
    if( 0 == data ) { return 0; }
    else{ return (data >> 1) + 1; }
    #endif
}

uint8_t get_zero_based_bit(uint32_t most_significant_bit)
{
    switch (most_significant_bit)
    {
        case UINT32_C(0x00000000): return  0;
        case UINT32_C(0x00000001): return  0;
        case UINT32_C(0x00000002): return  1;
        case UINT32_C(0x00000004): return  2;
        case UINT32_C(0x00000008): return  3;
        case UINT32_C(0x00000010): return  4;
        case UINT32_C(0x00000020): return  5;
        case UINT32_C(0x00000040): return  6;
        case UINT32_C(0x00000080): return  7;
        case UINT32_C(0x00000100): return  8;
        case UINT32_C(0x00000200): return  9;
        case UINT32_C(0x00000400): return 10;
        case UINT32_C(0x00000800): return 11;
        case UINT32_C(0x00001000): return 12;
        case UINT32_C(0x00002000): return 13;
        case UINT32_C(0x00004000): return 14;
        case UINT32_C(0x00008000): return 15;
        case UINT32_C(0x00010000): return 16;
        case UINT32_C(0x00020000): return 17;
        case UINT32_C(0x00040000): return 18;
        case UINT32_C(0x00080000): return 19;
        case UINT32_C(0x00100000): return 20;
        case UINT32_C(0x00200000): return 21;
        case UINT32_C(0x00400000): return 22;
        case UINT32_C(0x00800000): return 23;
        case UINT32_C(0x01000000): return 24;
        case UINT32_C(0x02000000): return 25;
        case UINT32_C(0x04000000): return 26;
        case UINT32_C(0x08000000): return 27;
        case UINT32_C(0x10000000): return 28;
        case UINT32_C(0x20000000): return 29;
        case UINT32_C(0x40000000): return 30;
        case UINT32_C(0x80000000): return 31;
        default: return 0;
    }
}

uint32_t push_over_to_left(uint32_t data, uint32_t most_significant_bit)
{
    switch (most_significant_bit)
    {
        case UINT32_C(0x00000000): return 0;
        case UINT32_C(0x00000001): return data << 31;
        case UINT32_C(0x00000002): return data << 30;
        case UINT32_C(0x00000004): return data << 29;
        case UINT32_C(0x00000008): return data << 28;
        case UINT32_C(0x00000010): return data << 27;
        case UINT32_C(0x00000020): return data << 26;
        case UINT32_C(0x00000040): return data << 25;
        case UINT32_C(0x00000080): return data << 24;
        case UINT32_C(0x00000100): return data << 23;
        case UINT32_C(0x00000200): return data << 22;
        case UINT32_C(0x00000400): return data << 21;
        case UINT32_C(0x00000800): return data << 20;
        case UINT32_C(0x00001000): return data << 19;
        case UINT32_C(0x00002000): return data << 18;
        case UINT32_C(0x00004000): return data << 17;
        case UINT32_C(0x00008000): return data << 16;
        case UINT32_C(0x00010000): return data << 15;
        case UINT32_C(0x00020000): return data << 14;
        case UINT32_C(0x00040000): return data << 13;
        case UINT32_C(0x00080000): return data << 12;
        case UINT32_C(0x00100000): return data << 11;
        case UINT32_C(0x00200000): return data << 10;
        case UINT32_C(0x00400000): return data <<  9;
        case UINT32_C(0x00800000): return data <<  8;
        case UINT32_C(0x01000000): return data <<  7;
        case UINT32_C(0x02000000): return data <<  6;
        case UINT32_C(0x04000000): return data <<  5;
        case UINT32_C(0x08000000): return data <<  4;
        case UINT32_C(0x10000000): return data <<  3;
        case UINT32_C(0x20000000): return data <<  2;
        case UINT32_C(0x40000000): return data <<  1;
        case UINT32_C(0x80000000): return data;
        default: return 0;
    }
}

uint32_t crc32_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit)
{
    // Runs through the loop until the zero flag is set.
    for (int i = 32; 0 != i; --i)
    {
        // Checks whether the negative flag (most significant bit (MSB)) is set.
        if (0 > (int32_t)data) { data ^= left_hand_polynomial; }
        data <<= 1;
    }
    return data >> (32 - bit);
}

uint32_t crc32(uint32_t data, uint32_t polynomial)
{
    uint32_t most_significant_bit;
    uint32_t left_hand_polynomial;
    uint8_t bit;

    most_significant_bit = get_most_significant_bit(polynomial);
    left_hand_polynomial = push_over_to_left(polynomial, most_significant_bit);
    bit = get_zero_based_bit(most_significant_bit);

    return crc32_speed(data, left_hand_polynomial, bit);
}

bool crc32_check_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit, uint32_t checksum)
{
    for (int i = 32; 0 != i; --i)
    {
        if (0 > (int32_t)data) { data ^= left_hand_polynomial; }
        data <<= 1;
    }
    return checksum == (data >> (32 - bit));
}

bool crc32_check(uint32_t data, uint32_t polynomial, uint32_t checksum)
{
    uint32_t most_significant_bit;
    uint32_t left_hand_polynomial;
    uint8_t bit;

    most_significant_bit = get_most_significant_bit(polynomial);
    left_hand_polynomial = push_over_to_left(polynomial, most_significant_bit);
    bit = get_zero_based_bit(most_significant_bit);

    return crc32_check_speed(data, left_hand_polynomial, bit, checksum);
}


/*---------------------------------------------------------------------*
 *  eof
 *---------------------------------------------------------------------*/
