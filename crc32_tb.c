/*---------------------------------------------------------------------*
 *  private: include files
 *---------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "crc32.h"


/*---------------------------------------------------------------------*
 *  info:
 *---------------------------------------------------------------------*/

// To use the test functions, copy the prototype into your file:
uint8_t crc32_test_execution(uint32_t data, uint32_t polynomial, uint32_t example_checksum);
uint8_t crc32_tests(void);


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

uint8_t crc32_test_execution(uint32_t data, uint32_t polynomial, uint32_t example_checksum)
{
    uint32_t checksum;
    uint32_t most_significant_bit;
	uint32_t left_hand_polynomial;
	uint8_t bit;
	bool equal;
    
    most_significant_bit = get_most_significant_bit(polynomial);
	left_hand_polynomial = push_over_to_left(polynomial, most_significant_bit);
	bit = get_zero_based_bit(most_significant_bit);
	
    checksum = crc32(data, left_hand_polynomial, bit);
	if(checksum != example_checksum) { return 1; }
	
	equal = crc32_check(data, left_hand_polynomial, bit, checksum);
	if(false == equal){ return 1; }
	
	return 0;
}

uint8_t crc32_tests(void)
{
	uint8_t error = 0;
	
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100110001                       ), 0x23      );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b11                              ), 0x1       );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b101                             ), 0x2       );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b110                             ), 0x2       );  
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001                            ), 0x4       );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10101                           ), 0x1       );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100101                          ), 0x9       );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001                         ), 0x27      );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10101001                        ), 0x26      );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100101001                       ), 0x2f      );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001001                      ), 0x199     );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10101001001                     ), 0x2f5     );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b101010010101                    ), 0x7e2     );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001010010101                   ), 0x711     );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10010100101001                  ), 0x023f    );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100100100101001                 ), 0x0bb7    );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001001001001                ), 0x73e1    );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10010010101001001               ), 0x97bc    );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100100100101001001              ), 0x0fc45   );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001001001001001             ), 0x37408   );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10101001001001001001            ), 0x14763   );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b101010010010010010101           ), 0x263f6   );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001010010010010010101          ), 0x17453d  );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10010100100100100101001         ), 0x3a2de6  );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100100100100100100101001        ), 0x48bf2d  );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001001001001001001001       ), 0x693dce  );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10101001001001001001001001      ), 0x1c10e30 );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b101010010010010010010010101     ), 0x291d7ef );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001010010010010010010010101    ), 0x1db2efd );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10010100100100100100100101001   ), 0x4a3d363 );
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b100100100100100100100100101001  ), 0x1901f6a9);
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b1001001001001001001001001001001 ), 0x2afb74e9);
	error += crc32_test_execution(0xE100CAFE, UINT32_C(0b10010010010010010101001001001001), 0x4a143fb7);

	return error;
}


/*---------------------------------------------------------------------*
 *  eof
 *---------------------------------------------------------------------*/
