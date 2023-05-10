/*************************************************************
 * 
 * Filename: SUART.h
 * Description: Header (interface) file of the SUART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SUART_H__
#define __SUART_H__
#include "STD_TYPES.h"

typedef enum{
	USART_enuOK,
	USART_enuNOK,
	USART_enuNullPtr,
	USART_enuBUSY,
	USART_enuIDLE,
}USART_ErrorStatus_t;

typedef enum{
	TX_IDLE,
	TX_BUSY,
	RX_IDLE,
	RX_BUSY,
}USART_RX_TX_Status_t;
typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}USART_Registers_t;

typedef struct {
	u8* TX_Buffer;
	u32 TX_Size;
	u32 TX_Idx;
	u8  TX_Status;
}TX_State;

typedef struct {
	u8* RX_Buffer;
	u32 RX_Size;
	u32 RX_Idx;
	u8  RX_Status;
}RX_State;

typedef struct {
	void* USART_Port;
	u32 USART_Pin;
	u32 USART_PinMode;
	u32 USART_ALternativeFunctionNumber;
}USART_ConfigPins;

/*USART_SR Bits*/
#define USART_SR_MASK   0x000003ff
#define USART_SR_PE		0 /*PE: Parity error*/
#define USART_SR_FE 	1 /*FE: Framing error*/
#define USART_SR_NF 	2 /*NF: Noise detected flag*/
#define USART_SR_ORE 	3 /*ORE: Overrun error*/
#define USART_SR_IDLE 	4 /* IDLE: IDLE line detected*/
#define USART_SR_RXNE 	5 /* RXNE: Read data register not empty*/
#define USART_SR_TC 	6 /* TC: Transmission complete*/
#define USART_SR_TXE 	7 /*TXE: Transmit data register empty*/
#define USART_SR_LBD 	8 /* LBD: LIN break detection flag*/
#define USART_SR_CTS 	9 /* CTS: CTS flag*/

/*USART_SR Bits Values*/
/*0 PE: Parity error
This bit is set by hardware when a parity error occurs in receiver mode.
 It is cleared by a software sequence (a read from the status register followed by a read or write access to the
USART_DR data register). The software must wait for the RXNE flag to be set before
clearing the PE bit.
*/
#define NO_PARITY_ERROR	0
#define PARITY_ERROR    1

/* FE: Framing error
This bit is set by hardware when a de-synchronization, excessive noise or a break character
is detected. It is cleared by a software sequence (an read to the USART_SR register
followed by a read to the USART_DR register).*/
#define NO_FRAMING_ERROR	0
#define FRAMING_ERROR   	1

/*NF: Noise detected flag
This bit is set by hardware when noise is detected on a received frame. It is cleared by a
software sequence (an read to the USART_SR register followed by a read to the
USART_DR register).*/
#define NO_NOISE_DETECTED	0
#define NOISE_DETECTED   	1

/*
ORE: Overrun error
This bit is set by hardware when the word currently being received in the shift register is
ready to be transferred into the RDR register while RXNE=1.
An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
 It is cleared by a software sequence (an read to the USART_SR register followed by a read to the USART_DR register)
*/
#define NO_OVERRUN_ERROR	0
#define OVERRUN_ERROR   	1

/*
 IDLE: IDLE line detected
This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the
IDLEIE=1 in the USART_CR1 register
*/
#define NO_IDLE_LINE_DETECTED	0
#define IDLE_LINE_DETECTED   	1

/*
 RXNE: Read data register not empty
This bit is set by hardware when the content of the RDR shift register has been transferred
to the USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1
register.
*/
#define DATA_NOT_RECIEVED	          0
#define DATA_RECIEVED_READY_TOBE_READ 1

/*
 TC: Transmission complete
This bit is set by hardware if the transmission of a frame containing data is complete and if
TXE is set. An interrupt is generated if TCIE=1 in the USART_CR1 register.
The TC bit can also be cleared by writing a '0' to it. This clearing
sequence is recommended only for multibuffer communication. */
#define TRANSMISSION_NOT_COMPLETE  0
#define TRANSMISSION_COMPLETED     1
/*
TXE: Transmit data register empty
This bit is set by hardware when the content of the TDR register has been transferred into
the shift register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It
is cleared by a write to the USART_DR register.The RXNE flag can also be
cleared by writing a zero to it. This clearing sequence is recommended only for multibuffer
communication.
*/
#define DATA_NOT_TRANSFERED_TO_SHIFT_REGISTER	0
#define DATA_TRANSFERED_TO_SHIFT_REGISTER		1

/*
 LBD: LIN break detection flag
This bit is set by hardware when the LIN break is detected. It is cleared by software (by
writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register
An interrupt is generated when LBD=1 if LBDIE=1
*/
#define NO_LIN_BREAK_DETECTED	0
#define LIN_BREAK_DETECTED		1

/*
 CTS: CTS flag
This bit is set by hardware when the CTS input toggles, if the CTSE bit is set. It is cleared by
software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3
register.*/
#define NO_CHANGE_ON_CTS_STATUS_LINE	0
#define CHANGE_ON_CTS_STATUS_LINE		1

/*Data register (USART_DR)*/
/*
 The Data register performs a double function (read and write) since it is composed of two
registers, one for transmission (TDR) and one for reception (RDR)
*/
#define USART_DR_MASK				 0x000001ff
/*Baud rate register (USART_BRR)*/
/*
 These 4 bits define the fraction of the USART Divider (USARTDIV). When OVER8=1, the
DIV_Fraction3 bit is not considered and must be kept cleared
*/
#define USART_BRR_DIV_FRACTION_MASK  0x0000000f
#define USART_BRR_DIV_MANTISSA_MASK  0x0000fff0

/*Control register 1 (USART_CR1) bits*/
#define USART_CR1_MASK 0x0000bfff
#define USART_CR1_SBK		0
#define USART_CR1_RWU 		1
#define USART_CR1_RE  		2
#define USART_CR1_TE  		3
#define USART_CR1_IDLEIE 	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE 	7
#define USART_CR1_PEIE 		8
#define USART_CR1_PS 		9
#define USART_CR1_PCE 		10
#define USART_CR1_WAKE 		11
#define USART_CR1_M 		12
#define USART_CR1_UE		13
#define USART_CR1_OVER8 	15

/*Bit 0 SBK: Send break*/
/*
 This bit set is used to send break characters. It can be set and cleared by software. It should
be set by software, and will be reset by hardware during the stop bit of break.*/
#define NO_BREAK_CHAR_TRANSMITTED 0
#define BREAK_CHAR_TRANSMITTED    1

/*Bit 1 RWU: Receiver wakeup*/
/*
 This bit determines if the USART is in mute mode or not. It is set and cleared by software
and can be cleared by hardware when a wakeup sequence is recognized.*/
#define ACTIVE_RECIEVER_MODE 0
#define MUTE_RECIEVER_MODE 1
/*
 Bit 2 RE: Receiver enable
This bit enables the receiver. It is set and cleared by software.
*/
#define RECIEVER_DISABLE 0
#define RECIEVER_ENABLE  1

/*Bit 3 TE: Transmitter enable
This bit enables the transmitter. It is set and cleared by software. */
#define TRANSMITTER_DISABLE 0
#define TRANSMITTER_ENABLE  1

/*Bit 4 IDLEIE: IDLE interrupt enable
 This bit is set and cleared by software*/
#define IDLE_INTERRUPT_DISABLE 0
#define IDLE_INTERRUPT_ENABLE  1

/*Bit 5 RXNEIE: RXNE interrupt enable
 This bit is set and cleared by software
 An USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR*/
#define RXNE_INTERRUPT_DISABLE 0
#define RXNE_INTERRUPT_ENABLE  1

/*Bit 6 TCIE: Transmission complete interrupt enable
This bit is set and cleared by software.*/
#define TC_INTERRUPT_DISABLE 0
#define TC_INTERRUPT_ENABLE  1

/*Bit 7 TXEIE: TXE interrupt enable
This bit is set and cleared by software.*/
#define TXE_INTERRUPT_DISABLE 0
#define TXE_INTERRUPT_ENABLE  1

/*Bit 8 PEIE: PE interrupt enable
This bit is set and cleared by software.*/
#define PE_INTERRUPT_DISABLE 0
#define PE_INTERRUPT_ENABLE  1

/*Bit 9 PS: Parity selection
This bit selects the odd or even parity when the parity generation/detection is enabled (PCE
bit set). It is set and cleared by software. The parity will be selected after the current byte*/
#define PS_EVEN_PARITY 0
#define PS_ODD_PARITY 1
/*Bit 10 PCE: Parity control enable
This bit selects the hardware parity control (generation and detection). When the parity
control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit
if M=0) and parity is checked on the received data. This bit is set and cleared by software.
Once it is set, PCE is active after the current byte (in reception and in transmission).
0: Parity control disabled
1: Parity control enabled*/
#define PARITY_CONTROL_DISABLED 0
#define PARITY_CONTROL_ENABLED  1
/*Bit 11 WAKE: Wakeup method
This bit determines the USART wakeup method, it is set or cleared by software.*/
#define WAKE_IDLE_LINE		0
#define WAKE_ADDRESS_MARK	1

/*Bit 12 M: Word length
This  bit determines the word length. It is set or cleared by software.*/
#define DATA_8_BITS 0
#define DATA_9_BITS 1

/*Bit 13 UE: USART enable
When this bit is cleared, the USART pre-scalers and outputs are stopped and the end of the
current byte transfer in order to reduce power consumption. This bit is set and cleared by
software.*/
#define USART_DISABLE 0
#define USART_ENABLE  1

/*Bit 15 OVER8: Over-Sampling mode
 Note: Over-sampling by 8 is not available in the Smart-card, IrDA and LIN modes: when
SCEN=1,IREN=1 or LINEN=1 then OVER8 is forced to ‘0 by hardware*/
#define OVER_SAMPLING_BY16 0
#define OVER_SAMPLING_BY8  1

/*Control register 2 (USART_CR2)*/
#define USART_CR2_MASK 0x00007f6f

#define USART_CR2_ADD	0
#define USART_CR2_LBDL  5
#define USART_CR2_LBDIE 6
#define USART_CR2_LBCL  8
#define USART_CR2_CPHA  9
#define USART_CR2_CPOL  10
#define USART_CR2_CLKEN 11
#define USART_CR2_STOP  12
#define USART_CR2_LINEN 14

/*
 Bits 3:0 ADD[3:0]: Address of the USART node
This bit-field gives the address of the USART node.
This is used in multiprocessor communication during mute mode, for wake up with address mark
detection.*/
#define USART_CR2_ADD_MASK 0xf

/*Bit 5 LBDL: lin break detection length
This bit is for selection between 11 bit or 10 bit break detection.
0: 10-bit break detection
1: 11-bit break detection */
#define LIN_BD_10_BIT 0
#define LIN_BD_11_BIT 1

/*Bit 6 LBDIE: LIN break detection interrupt enable
Break interrupt mask (break detection using break delimiter)*/
#define LIN_BD_INTERRUPT_ENABLE 0
#define LIN_BD_INTERRUPT_DISABLE 1

/*Bit 8 LBCL: Last bit clock pulse
This bit allows the user to select whether the clock pulse associated with the last data bit
transmitted (MSB) has to be output on the CK pin in synchronous mode.
1: The last bit is the 8th or 9th data bit transmitted depending on the 8 or 9 bit format selected
by the M bit in the USART_CR1 register.*/
#define LBCL_NOT_OUTPUT 0
#define LBCL_OUTPUT 	1

/*Bit 9 CPHA: Clock phase
This bit allows the user to select the phase of the clock output on the CK pin in synchronous mode.
It works in conjunction with the CPOL bit to produce the desired clock/data relationship (see figures
179 to 180)
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge*/
#define CPHA_FIRST_CLK_TRANSITION  0
#define CPHA_SECOND_CLK_TRANSITION 1

/*Bit 10 CPOL: Clock polarity
 This bit allows the user to select the polarity of the clock output on the CK pin in synchronous mode.
It works in conjunction with the CPHA bit to produce the desired clock/data relationship */
#define CPOL_LOW  0
#define CPOL_HIGH 1

/*Bit 11 CLKEN: Clock enable
This bit allows the user to enable the CK pin.*/
#define CK_DISABLE 0
#define CK_ENABLE  1

/*Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.*/
#define STOP_1_BIT   00
#define STOP_0_5_BIT 01
#define STOP_2_BIT   10
#define STOP_1_5_BIT 11

/*Bit 14 LINEN: LIN mode enable
This bit is set and cleared by software.
0: LIN mode disabled
1: LIN mode enabled
The LIN mode enables the capability to send LIN Synch Breaks (13 low bits) using the SBK bit in
the USART_CR1 register, and to detect LIN Sync breaks.*/
#define LIN_MODE_DISABLED 0
#define LIN_MODE_ENABLED  1

/*Control register 3 (USART_CR3)*/

#define USART_CR3_EIE		0
#define USART_CR3_IREN		1
#define USART_CR3_IRLP		2
#define USART_CR3_HDSEL		3
#define USART_CR3_NACK		4
#define USART_CR3_SCEN		5
#define USART_CR3_DMAR		6
#define USART_CR3_DMAT		7
#define USART_CR3_RTSE		8
#define USART_CR3_CTSE		9
#define USART_CR3_CTSIE		10
#define USART_CR3_ONEBIT	11

/*Bit 0 EIE: Error interrupt enable
Error Interrupt Enable Bit is required to enable interrupt generation in case of a framing
error, overrun error or noise flag (FE=1 or ORE=1 or NF=1 in the USART_SR register) in
case of Multi Buffer Communication (DMAR=1 in the USART_CR3 register).
0: Interrupt is inhibited
1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or
ORE=1 or NF=1 in the USART_SR register.*/
#define ERROR_INTERRUPT_INHIBITED 0
#define ERROR_INTERRUPT_GENERATED 1

/*Bit 1 IREN: IrDA mode enable
This bit is set and cleared by software*/
#define IrDA_DISABLE  0
#define IrDA_ENABLE   1
/* Bit 2 IRLP: IrDA low-power
This bit is used for selecting between normal and low-power IrDA modes*/
#define IRLP_NORMAL_MODE	 0
#define IRLP_LOW_POWER_MODE  1

/*Bit 3 HDSEL: Half-duplex selection
Selection of Single-wire Half-duplex mode */
#define HALF_DUPLEX_NOT_SELECTED  0
#define HALF_DUPLEX_SELECTED 	  1

/*Bit 4 NACK: Smartcard NACK enable
Note: 0: NACK transmission in case of parity error is disabled
1: NACK transmission during parity error is enabled*/
#define NACK_PE_DISABLED  0
#define NACK_PE_ENABLED   1

/*Bit 5 SCEN: Smartcard mode enable
This bit is used for enabling Smartcard mode.*/
#define SC_MODE_DISABLED  0
#define SC_MODE_ENABLED   1

/*6 DMAR: DMA enable receiver
This bit is set/reset by software*/
#define DMA_RECEIVER_MODE_DISABLED  0
#define DMA_RECEIVER_MODE_ENABLED   1

/*Bit 7 DMAT: DMA enable transmitter
This bit is set/reset by software
1: DMA mode is enabled for transmission.
0: DMA mode is disabled for transmission.*/
#define DMA_TRANSMITTER_MODE_DISABLED  0
#define DMA_TRANSMITTER_MODE_ENABLED   1

/*Bit 8 RTSE: RTS enable*/
#define RTS_INTERRUPT_DISABLE  0
#define RTS_INTERRUPT_ENABLE  1

/*Bit 9 CTSE: CTS enable*/
#define CTS_MODE_DISABLE  0
#define CTS_MODE_ENABLE  1

/*Bit 10 CTSIE: CTS interrupt enable*/
#define CTS_INTERRUPT_INHIBITED  0
#define CTS_INTERRUPT_GENERATED  1

/*Bit 11 ONEBIT: One sample bit method enable
This bit allows the user to select the sample method. When the one sample bit method is
selected the noise detection flag (NF) is disabled.*/
#define THREE_SAMPLE_BIT_METHOD  0
#define ONE_SAMPLE_BIT_METHOD    1

/*Guard time and prescaler register (USART_GTPR)*/


/*APIs*/
void USART1_vidInit(void);
void USART2_vidInit(void);
USART_ErrorStatus_t USART_getCTSFlagState(u8* CTSFlagState);
USART_ErrorStatus_t USART_clearCTSFlagState();

USART_ErrorStatus_t USART_getLINBreakDetectionState(u8* LINBreakDetectionState);
USART_ErrorStatus_t USART_clearLINBreakDetectionState();

/* TXE bit
 * TransmitRegisterState=1 if  Data is transferred to the shift register  when the content of
 * the TDR register has been transferred into the shift register
 * TransmitRegisterState=0 if  Data is not transferred to the shift register
 * Note: This API is used during single buffer transmission.*/
USART_ErrorStatus_t USART_getDataTransmitRegisterState(u8* TransmitRegisterState);
USART_ErrorStatus_t USART_clearDataTransmitRegisterState();

/*TC bit
 * DataTransmissionState=1 if Transmission is complete
 * DataTransmissionState=0 if Transmission is not complete
 * */
USART_ErrorStatus_t USART_getTransmittedDataState(u8* DataTransmissionState);
USART_ErrorStatus_t USART_clearTransmittedDataState();
/*RXNE bit
 *DataReceiveState =1 if Received data is ready to be read
 *DataReceiveState =0 if Data is not received
 *Note: when the content of the RDR shift register has been transferred
to the USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
*/
USART_ErrorStatus_t USART_getReceivedDataState(u8* DataReceiveState);
USART_ErrorStatus_t USART_clearReceivedDataState();

/*IDLE bit
 when an Idle Line is detected. An interrupt is generated if the IDLEIE=1 in the USART_CR1 register.
 0: No Idle Line is detected
1: Idle Line is detected*/
USART_ErrorStatus_t USART_getIDLELineDetection(u8* IDLE_LineDetection);
USART_ErrorStatus_t USART_clearIDLELineDetection();

/*ORE BIT
 * when the word currently being received in the shift register is
ready to be transferred into the RDR register while RXNE=1. An interrupt is generated if
RXNEIE=1 in the USART_CR1 register
OverRunErrorDetection=0 if No Overrun error
OverRunErrorDetection=1 if Overrun error is detected

Note: When this bit is set, the RDR register content will not be lost but the shift register will be
overwritten. An interrupt is generated on ORE flag in case of Multi Buffer
communication if the EIE bit is set.
*/
USART_ErrorStatus_t USART_getOverRunErrorDetection(u8* OverRunErrorDetection);
USART_ErrorStatus_t USART_clearOverRunErrorDetection();

/*NF BIT
 * 0: No noise is detected
 * 1: Noise is detected when noise is detected on a received frame
 * Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupting interrupt is generated on NF flag in case of Multi
Buffer communication if the EIE bit is set.

Note: When the line is noise-free, the NF flag can be disabled by programming the ONEBIT
bit to 1 to increase the USART tolerance to deviations */
USART_ErrorStatus_t USART_getNoiseFlagDetection(u8* NoiseDetection);
USART_ErrorStatus_t USART_clearNoiseFlagDetection();

/*FE BIT
 * 0: No Framing error is detected
1: Framing error or break character is detected  when a de-synchronization, excessive noise or a break character is detected.
Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupt. If the word currently being transferred causes both
frame error and overrun error, it will be transferred and only the ORE bit will be set.
An interrupt is generated on FE flag in case of Multi-Buffer communication if the EIE bit is set.*/
USART_ErrorStatus_t USART_getFramingFlagDetection(u8* FramingFlagDetection);
USART_ErrorStatus_t USART_clearFramingFlagDetection();

/*PE BIT
 *0: No parity error
1: Parity error e when a parity error occurs in receiver mode.
The software must wait for the RXNE flag to be set before clearing the PE bit.
An interrupt is generated if PEIE = 1 in the USART_CR1 register. */
USART_ErrorStatus_t USART_getParityErrorDetection(u8* ParityErrorDetection);
USART_ErrorStatus_t USART_clearParityErrorDetection();

/*Contains the Received or Transmitted data character, depending on whether it is read from
or written to.
The Data register performs a double function (read and write) since it is composed of two
registers, one for transmission (TDR) and one for reception (RDR).
The TDR register provides the parallel interface between the internal bus and the output shift
register (see Figure 1).
The RDR register provides the parallel interface between the input shift register and the
internal bus.
When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the
value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because
it is replaced by the parity.
When receiving with the parity enabled, the value read in the MSB bit is the received parity
bit.*/
USART_ErrorStatus_t USART_getRecievedData(u16* RecievedData);
USART_ErrorStatus_t USART_setTransmittedData(u16 TransmittedData);
/*
Bits 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV
These 12 bits define the mantissa of the USART Divider (USARTDIV)
Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV
These 4 bits define the fraction of the USART Divider (USARTDIV). When OVER8=1, the
DIV_Fraction3 bit is not considered and must be kept cleared.*/
USART_ErrorStatus_t USART_SetBaudRateValue(f32 BaudRateValue);

/*options:

USART_CR1_IDLEIE:  IDLE interrupt
USART_CR1_RXNEIE: RXNE interrupt
USART_CR1_TCIE : Transmission complete interrupt
USART_CR1_TXEIE: TXE interrupt
USART_CR1_PEIE: PE interrupt
*/
USART_ErrorStatus_t USART_enableInterruptX(u8 USART_CR1_InterruptName);
USART_ErrorStatus_t USART_disableInterruptX(u8 USART_CR1_InterruptName);

USART_ErrorStatus_t USART_enableUART();
USART_ErrorStatus_t USART_disableUART();

/*
USART_CR1_RE : Receiver enable
USART_CR1_TE : Transmitter enable
USART_CR1_PCE: Parity controL
*/
USART_ErrorStatus_t USART_enable_TX_RX_PC(u8 USART_CR1_BitName);
USART_ErrorStatus_t USART_disable_TX_RX_PC(u8 USART_CR1_BitName);

/*
 * Options: OVER_SAMPLING_BY16, OVER_SAMPLING_BY8
 */
USART_ErrorStatus_t USART_setOverSamplingMode(u8 OVER_SAMPLING_BY);

/*
 * Options: DATA_8_BITS,DATA_9_BITS
 */
USART_ErrorStatus_t USART_setWordLength(u8 DATA_x_BITS);

/*
 *Options: WAKE_IDLE_LINE, WAKE_ADDRESS_MARK
 */
USART_ErrorStatus_t USART_setWakeUpMode(u8 WAKE_);

/*
 *Options:PS_EVEN_PARITY, PS_ODD_PARITY
 */
USART_ErrorStatus_t USART_selectParity(u8 PS_x_PARITY);

/*
 *Options:ACTIVE_RECIEVER_MODE, MUTE_RECIEVER_MODE
 */
USART_ErrorStatus_t USART_setReceiverWakeUpMode(u8 x_RECIEVER_MODE);

/*
 *Options:NO_BREAK_CHAR_TRANSMITTED, BREAK_CHAR_TRANSMITTED
 */
USART_ErrorStatus_t USART_setSendBreak(u8 x_BREAK_CHAR_TRANSMITTED);

/*Control register 2 (USART_CR2) APIs*/
/*
 * Options: STOP_1_BIT,STOP_0_5_BIT,STOP_2_BIT,STOP_1_5_BIT 11*/
USART_ErrorStatus_t USART_selectStopBits(u32 STOP_X_BIT );

/*
 * This bit-field gives the address of the USART node.
This is used in multiprocessor communication during mute mode, for wake up with address mark detection*/
USART_ErrorStatus_t USART_setWakeUpAddressMark(u32 ADD_);
/*
 * Options:LIN_MODE_DISABLED,LIN_MODE_ENABLED*/
USART_ErrorStatus_t USART_setLINMode(u8 LIN_MODE_);

/*
 * Options:CK_:CK_DISABLE,CK_ENABLE
 * (CLOCK POLARITY) CPOL_:CPOL_HIGH,CPOL_LOW
 * (CLOCK PHASE) CPHA_ : CPHA_FIRST_CLK_TRANSITION,CPHA_SECOND_CLK_TRANSITION
 * (Last bit clock pulse) LBCL_: LBCL_NOT_OUTPUT,LBCL_OUTPUT
 * */
USART_ErrorStatus_t USART_configClkPin(u8 CK_,u8 CPOL_, u8 CPHA_, u8  LBCL_);

/*
 *Options: LIN_BD_INTERRUPT_ENABLE,LIN_BD_INTERRUPT_DISABLE
 */
USART_ErrorStatus_t USART_setLINBreakDetectionInterrupt(u8 LIN_BD_INTERRUPT_);

/*
 *Options: LIN_BD_11_BIT,LIN_BD_10_BIT
 */
USART_ErrorStatus_t USART_setLINBreakDetectionLength(u8 LIN_BD_X_BIT);

/*
 *Options: ERROR_INTERRUPT_INHIBITED,ERROR_INTERRUPT_GENERATED
 */
USART_ErrorStatus_t USART_setErrorInterrupt(u8 ERROR_INTERRUPT_);

/*
 * Options:(IrDA mode) IrDA_: IrDA_DISABLE,IrDA_ENABLE
 * (IrDA low-power) IRLP_:IRLP_NORMAL_MODE,IRLP_LOW_POWER_MODE
 * */
USART_ErrorStatus_t USART_configIrDA(u8 IrDA_,u8 IRLP_);

/*
 *Options: HALF_DUPLEX_NOT_SELECTED,HALF_DUPLEX_SELECTED
 */
USART_ErrorStatus_t USART_setLHalfDuplexSelection(u8 HALF_DUPLEX_);

/*
 * Options:SC_MODE_: SC_MODE_DISABLED,SC_MODE_ENABLED
 *  NACK_PE_:NACK_PE_DISABLED,NACK_PE_DISABLED
 * */
USART_ErrorStatus_t USART_configSmartCardMode(u8 SC_MODE_,u8 NACK_PE_);

/*
 *Options: DMA_TRANSMITTER_MODE_DISABLED,DMA_TRANSMITTER_MODE_ENABLED
 * DMA_RECEIVER_MODE_:DMA_RECEIVER_MODE_DISABLED,DMA_RECEIVER_MODE_ENABLED
 */
USART_ErrorStatus_t USART_setDMATransmitter_ReceiverMode(u8 DMA_TRANSMITTER_MODE_, u8 DMA_RECEIVER_MODE_);

/*
 *Options: RTS_INTERRUPT_DISABLE,RTS_INTERRUPT_ENABLE
 */
USART_ErrorStatus_t USART_setRTSInterrupt(u8 RTS_INTERRUPT_);

/*
 *Options: CTS_MODET_DISABLE,CTS_MODE_ENABLE
 */
USART_ErrorStatus_t USART_setCTSMode(u8 CTS_MODE_);

/*
 *Options: CTS_INTERRUPT_INHIBITED,CTS_INTERRUPT_GENERATED
 */
USART_ErrorStatus_t USART_setCTSInterrupt(u8 CTS_INTERRUPT_);


/*
 *Options: THREE_SAMPLE_BIT_METHOD,ONE_SAMPLE_BIT_METHOD
 */
USART_ErrorStatus_t USART_setSampleBitMethod(u8 X_SAMPLE_BIT_METHOD);

USART_ErrorStatus_t USART_sendBuffer(u8 *Buffer,u32 Size);
USART_ErrorStatus_t USART_receiveBuffer(u8* Buffer,u32 Size);

USART_ErrorStatus_t USART_RX_setCallBack( void(* AppNotifyRX_MAIN)(void) );
USART_ErrorStatus_t USART_TX_setCallBack( void(* AppNotifyTX_MAIN)(void) );

void AppNotifyRX_main(void);
void AppNotifyTX_main(void);
#endif /* __SUART_H__ */
