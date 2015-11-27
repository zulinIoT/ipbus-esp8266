/*
 * Autor: Salvador Gurt Pla
*/

/**
 * @file ipbus.h
 * @brief Implementation of IPBus protocol
 *
 * @author Salvador Gurt Pla
 * @date November 2015
 * @bug Nothing detected yet
 */

/*
 * IPBus packet header
 *--------------------------------------------------------------------------------------
 *| 31 				24 | 23 			16 | 15			 8 | 7			 			0  |
 *--------------------------------------------------------------------------------------
 *| Protocol  |	Rsvd.  |		Packet ID (16 bits)    	   | Byte-order  | Packet Type |
 *| version   |		   |						   		   | qualifier   |			   |
 *|------------------------------------------------------------------------------------|
 *|		0x2	  |   0    |			0x0 - 0xFFFF		   |  	0xF      | 0x0 - 0x2   |
 *--------------------------------------------------------------------------------------
 *
 * Packet types
 * Packet Type value 		Direction 			Meaning
 * 0x0 						Both 				Control packet (i.e. contains IPbus transactions)
 * 0x1 						Both 				Status packet
 * 0x2 						Request 			Re-send request packet
 * 0x3 – 0xf 				n/a 				Rsvd.
 */

//Packet type definition
#define CONTROL_PACKET 	0x0
#define STATUS_PACKET	0x1
#define RESEND_PACKET 	0x2

//Header masks
#define PROTOCOL_VERSION_MASK		0x20000000
#define PACKET_ID_MASK				0x00FFFF00
#define BYTE_ORDER_MASK				0x000000F0
#define PACKET_TYPE_MASK			0x0000000F

//Constants
#define MAX_PACKET_SIZE 1500

/*
 * IPBus Transaction header
 *
 * Each IPBus request and reply transaction must start with a 32-bit header with the following
 * format:
 *--------------------------------------------------------------------------------------------------
 *| 31 				28 | 27 						16 | 15			 8 | 7		   4 | 3		0  |
 *--------------------------------------------------------------------------------------------------
 *| Protocol  version  | Transaction ID (12 bits)      | 	 Words     | Type ID 	 |  Info Code  |
 *| 	( 4 bits) 	   |						   	   |  ( 8 bits )   | ( 4 bits )	 |  ( 4 bits ) |
 *--------------------------------------------------------------------------------------------------
 *
 * Protocol version ( four bits 31 -> 28
 *   - should be set to 2 for this version
 * Transaction ID ( 12 bits 27 -> 16
 *   - Transaction identification, so the client/target can track each transaction
 * Words ( 8 bits 15 -> 8 )
 *   - Number of words for that transaction
 * Type ID ( 4 bits -> 7 -> 4 )
 *   - Define the type of IPBus transaction ( read / write )
 * Info Code ( 4 bits 3 -> 0 )
 *   - Defines the direction and error state of the transaction request/response
 */

//Info code defines
#define REQUEST_SUCCESS 0x0
#define BAD_HEADER 0x1
#define READ_BUS_ERROR 0x4
#define WRITE_BUS_ERROR 0x5
#define READ_BUS_TIMEOUT 0x6
#define WRITE_BUS_TIMEOUT 0x7
#define UKNOWN_REQUEST 0xF


