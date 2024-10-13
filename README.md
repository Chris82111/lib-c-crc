# crc32

This repository calculates a Cyclic Redundancy Check (CRC) for a 32 bit number without a table.
Since no table is used, 32-bit numbers can be used both as data and as polynomials.

## Available functions

All publicly usable functions are listed and described in [`crc32.h`](crc32.h). Here is a shortened excerpt:

```c
uint32_t crc32(uint32_t data, uint32_t polynomial);
```

```c
bool crc32_check(uint32_t data, uint32_t polynomial, uint32_t checksum);
```

```c
uint32_t crc32_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit);
```

```c
bool crc32_check_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit, uint32_t checksum);
```

## Main algorithm

The main algorithm for calculating the CRC is shown below:

```c
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
```

## Acknowledgement

Very good sources are:

- [Description of CRC](http://www.ross.net/crc/download/crc_v3.txt)
- [Online CRC calculator](https://www.ghsi.de/pages/subpages/Online%20CRC%20Calculation/index.php?Polynom=10101000&Message=E100CAFE)
