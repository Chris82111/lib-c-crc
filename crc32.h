#ifndef INC_CRC32_H_
#define INC_CRC32_H_

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------*
 *  public: include files
 *---------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>


/*---------------------------------------------------------------------*
 *  public: define
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  public: typedefs
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  public: extern variables
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  public: function prototypes
 *---------------------------------------------------------------------*/

//! @brief  Deletes all bits except for the most significant bit
//! @param  data The bit pattern Only the most significant bit
//! @return Data with only the most significant bit 
uint32_t get_most_significant_bit(uint32_t data);

//! @brief  Get the highest set bit of a right-aligned polynomial counted zero-based.
//! @param  most_significant_bit Only the most significant bit
//! @return Highest set bit counted zero-based.
uint8_t get_zero_based_bit(uint32_t most_significant_bit);

//! @brief  Moves the bits to the left
//! @param  data The bit pattern
//! @param  most_significant_bit Only the most significant bit
//! @return Moved bit pattern
uint32_t push_over_to_left(uint32_t data, uint32_t most_significant_bit);

//! @brief  Function for calculating a crc
//! @param  data The data on which you want to create the checksum
//! @param  left_hand_polynomial Check polynomial, left-aligned, highest and lowest bit must be a 1.
//!         E.g. push_over_to_left(polynomial, get_most_significant_bit(polynomial)).
//!         Use a constant to speed up the calculation.
//! @param  bit Highest set bit of a right-aligned polynomial counted zero-based.
//!         E.g. get_zero_based_bit(get_most_significant_bit(polynomial));
//!         Use a constant to speed up the calculation.
//! @return The calculated checksum
uint32_t crc32_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit);

//! @brief  Function for calculating a crc
//! @param  data The data on which you want to create the checksum
//! @param  polynomial Check polynomial, highest and lowest bit must be a 1.
//! @return The calculated checksum
uint32_t crc32(uint32_t data, uint32_t polynomial);

//! @brief  Function for checking whether the specified checksum matches the data
//! @param  data The data on which you want to create the checksum
//! @param  left_hand_polynomial Check polynomial, left-aligned, highest and lowest bit must be a 1.
//!         E.g. push_over_to_left(polynomial, get_most_significant_bit(polynomial)).
//!         Use a constant to speed up the calculation.
//! @param  bit Highest set bit of a right-aligned polynomial counted zero-based.
//!         E.g. get_zero_based_bit(get_most_significant_bit(polynomial));
//!         Use a constant to speed up the calculation.
//! @param  checksum The checksum to be validated
//! @return true  The checksum matches the data and the polynomial
//! @return false The checksum does not match the data and the polynomial
bool crc32_check_speed(uint32_t data, uint32_t left_hand_polynomial, uint8_t bit, uint32_t checksum);

//! @brief  Function for checking whether the specified checksum matches the data
//! @param  data The data on which you want to create the checksum
//! @param  polynomial Check polynomial, highest and lowest bit must be a 1.
//! @param  checksum The checksum to be validated
//! @return true  The checksum matches the data and the polynomial
//! @return false The checksum does not match the data and the polynomial
bool crc32_check(uint32_t data, uint32_t polynomial, uint32_t checksum);


/*---------------------------------------------------------------------*
 *  public: static inline functions
 *---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*
 *  eof
 *---------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* INC_CRC32_H_ */
