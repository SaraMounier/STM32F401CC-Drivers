/*************************************************************
 * 
 * Filename: DMA.h
 * Description: Header (interface) file of the DMA driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __DMA_H__
#define __DMA_H__
#include "STD_TYPES.h"

#define DMA1  (void*)(0x40026000)
#define DMA2  (void*)(0x40026400)
#define DMA_StreamsNumber 8

typedef enum {
	DMA_enuOK,
	DMA_enuNOK,
	DMA_enuNullPtr,
}DMA_ErrorStatus_t;

typedef struct{
	u32 DMA_SxCR;
	u32 DMA_SxNDTR;
	u32 DMA_SxPAR;
	u32 DMA_SxM0AR;
	u32 DMA_SxM1AR ;
	u32 DMA_SxFCR;
}DMA_Streamx_Registers;

typedef struct
{
	u32 DMA_LISR;
	u32 DMA_HISR;
	u32 DMA_LIFCR;
	u32 DMA_HIFCR;
	DMA_Streamx_Registers StreamRegs[DMA_StreamsNumber];
}DMA_Registers_t;

/*DMA low interrupt status register*/
typedef enum
{
	DMA_enuLISR_FEIF0,
	DMA_enuLISR_Reserved00,
	DMA_enuLISR_DMEIF0,
	DMA_enuLISR_TEIF0,
	DMA_enuLISR_HTIF0,
	DMA_enuLISR_TCIF0,
	DMA_enuLISR_FEIF1,
	DMA_enuLISR_Reserved01,
	DMA_enuLISR_DMEIF1,
	DMA_enuLISR_TEIF1,
	DMA_enuLISR_HTIF1,
	DMA_enuLISR_TCIF1,
	DMA_enuLISR_Reserved02,
	DMA_enuLISR_Reserved03,
	DMA_enuLISR_Reserved04,
	DMA_enuLISR_Reserved05,
	DMA_enuLISR_FEIF2,
	DMA_enuLISR_Reserved06,
	DMA_enuLISR_DMEIF2,
	DMA_enuLISR_TEIF2,
	DMA_enuLISR_HTIF2,
	DMA_enuLISR_TCIF2,
	DMA_enuLISR_FEIF3,
	DMA_enuLISR_Reserved07,
	DMA_enuLISR_DMEIF3,
	DMA_enuLISR_TEIF3,
	DMA_enuLISR_HTIF3,
	DMA_enuLISR_TCIF3,
	DMA_enuLISR_Reserved08,
	DMA_enuLISR_Reserved09,
	DMA_enuLISR_Reserved10,
	DMA_enuLISR_Reserved11,
}DMA_enuLISR;

typedef enum{
	DMA_enuHISR_FEIF4=32,
	DMA_enuHISR_Reserved00,
	DMA_enuHISR_DMEIF4,
	DMA_enuHISR_TEIF4,
	DMA_enuHISR_HTIF4,
	DMA_enuHISR_TCIF4,
	DMA_enuHISR_FEIF5,
	DMA_enuHISR_Reserved01,
	DMA_enuHISR_DMEIF5,
	DMA_enuHISR_TEIF5,
	DMA_enuHISR_HTIF5,
	DMA_enuHISR_TCIF5,
	DMA_enuHISR_Reserved02,
	DMA_enuHISR_Reserved03,
	DMA_enuHISR_Reserved04,
	DMA_enuHISR_Reserved05,
	DMA_enuHISR_FEIF6,
	DMA_enuHISR_Reserved06,
	DMA_enuHISR_DMEIF6,
	DMA_enuHISR_TEIF6,
	DMA_enuHISR_HTIF6,
	DMA_enuHISR_TCIF6,
	DMA_enuHISR_FEIF7,
	DMA_enuHISR_Reserved07,
	DMA_enuHISR_DMEIF7,
	DMA_enuHISR_TEIF7,
	DMA_enuHISR_HTIF7,
	DMA_enuHISR_TCIF7,
	DMA_enuHISR_Reserved08,
	DMA_enuHISR_Reserved09,
	DMA_enuHISR_Reserved10,
	DMA_enuHISR_Reserved11,
}DMA_enuHISR;


/*DMA low interrupt flag clear register*/
typedef enum {
	DMA_enuLIFCR_CFEIF0=64,
	DMA_enuLIFCR_Reserved00,
	DMA_enuLIFCR_CDMEIF0,
	DMA_enuLIFCR_CTEIF0,
	DMA_enuLIFCR_CHTIF0,
	DMA_enuLIFCR_CTCIF0,
	DMA_enuLIFCR_CFEIF1,
	DMA_enuLIFCR_Reserved01,
	DMA_enuLIFCR_CDMEIF1,
	DMA_enuLIFCR_CTEIF1,
	DMA_enuLIFCR_CHTIF1,
	DMA_enuLIFCR_CTCIF1,
	DMA_enuLIFCR_Reserved02,
	DMA_enuLIFCR_Reserved03,
	DMA_enuLIFCR_Reserved04,
	DMA_enuLIFCR_Reserved05,
	DMA_enuLIFCR_CFEIF2,
	DMA_enuLIFCR_Reserved06,
	DMA_enuLIFCR_CDMEIF2,
	DMA_enuLIFCR_CTEIF2,
	DMA_enuLIFCR_CHTIF2,
	DMA_enuLIFCR_CTCIF2,
	DMA_enuLIFCR_CFEIF3,
	DMA_enuLIFCR_Reserved07,
	DMA_enuLIFCR_CDMEIF3,
	DMA_enuLIFCR_CTEIF3,
	DMA_enuLIFCR_CHTIF3,
	DMA_enuLIFCR_CTCIF3,
	DMA_enuLIFCR_Reserved08,
	DMA_enuLIFCR_Reserved09,
	DMA_enuLIFCR_Reserved10,
	DMA_enuLIFCR_Reserved11,
}DMA_enuLIFCR;
typedef enum {
	DMA_enuHIFCR_CFEIF4=96,
	DMA_enuHIFCR_Reserved00,
	DMA_enuHIFCR_CDMEIF4,
	DMA_enuHIFCR_CTEIF4,
	DMA_enuHIFCR_CHTIF4,
	DMA_enuHIFCR_CTCIF4,
	DMA_enuHIFCR_CFEIF5,
	DMA_enuHIFCR_Reserved01,
	DMA_enuHIFCR_CDMEIF5,
	DMA_enuHIFCR_CTEIF5,
	DMA_enuHIFCR_CHTIF5,
	DMA_enuHIFCR_CTCIF5,
	DMA_enuHIFCR_Reserved02,
	DMA_enuHIFCR_Reserved03,
	DMA_enuHIFCR_Reserved04,
	DMA_enuHIFCR_Reserved05,
	DMA_enuHIFCR_CFEIF6,
	DMA_enuHIFCR_Reserved06,
	DMA_enuHIFCR_CDMEIF6,
	DMA_enuHIFCR_CTEIF6,
	DMA_enuHIFCR_CHTIF6,
	DMA_enuHIFCR_CTCIF6,
	DMA_enuHIFCR_CFEIF7,
	DMA_enuHIFCR_Reserved07,
	DMA_enuHIFCR_CDMEIF7,
	DMA_enuHIFCR_CTEIF7,
	DMA_enuHIFCR_CHTIF7,
	DMA_enuHIFCR_CTCIF7,
	DMA_enuHIFCR_Reserved08,
	DMA_enuHIFCR_Reserved09,
	DMA_enuHIFCR_Reserved10,
	DMA_enuHIFCR_Reserved11,
}DMA_enuHIFCR;

typedef enum {
	DMA_enuSxCR_EN,
	DMA_enuSxCR_DMEIE,
	DMA_enuSxCR_TEIE,
	DMA_enuSxCR_HTIE,
	DMA_enuSxCR_TCIE,
	DMA_enuSxCR_PFCTRL,
	DMA_enuSxCR_DIR0,
	DMA_enuSxCR_DIR1,
	DMA_enuSxCR_CIRC,
	DMA_enuSxCR_PINC,
	DMA_enuSxCR_MINC,
	DMA_enuSxCR_PSIZE0,
	DMA_enuSxCR_PSIZE1,
	DMA_enuSxCR_MSIZE0,
	DMA_enuSxCR_MSIZE1,
	DMA_enuSxCR_PINCOS,
	DMA_enuSxCR_PL0,
	DMA_enuSxCR_PL1,
	DMA_enuSxCR_DBM,
	DMA_enuSxCR_CT,
	DMA_enuSxCR_Reserved0,
	DMA_enuSxCR_PBURST0,
	DMA_enuSxCR_PBURST1,
	DMA_enuSxCR_MBURST0,
	DMA_enuSxCR_MBURST1,
	DMA_enuSxCR_CHSEL0,
	DMA_enuSxCR_CHSEL1,
	DMA_enuSxCR_CHSEL2,
	DMA_enuSxCR_Reserved1,
	DMA_enuSxCR_Reserved2,
	DMA_enuSxCR_Reserved3,
	DMA_enuSxCR_Reserved4,
}DMA_enuSxCR;


#define NDT_MASK 0x0000ffff
#define DMA_enuSxFCR_FTH0  0
#define DMA_enuSxFCR_FTH1  1
#define DMA_enuSxFCR_DMDIS 2
#define DMA_enuSxFCR_FS0   3
#define DMA_enuSxFCR_FS1   4
#define DMA_enuSxFCR_FS2   5
#define DMA_enuSxFCR_FEIE  7

#define DMA_STREAM_0    0b000
#define DMA_STREAM_1    0b001
#define DMA_STREAM_2    0b010
#define DMA_STREAM_3    0b011
#define DMA_STREAM_4    0b100
#define DMA_STREAM_5    0b101
#define DMA_STREAM_6    0b110
#define DMA_STREAM_7    0b111


#define DMA_CHANNEL_0    0b000
#define DMA_CHANNEL_1    0b001
#define DMA_CHANNEL_2    0b010
#define DMA_CHANNEL_3    0b011
#define DMA_CHANNEL_4    0b100
#define DMA_CHANNEL_5    0b101
#define DMA_CHANNEL_6    0b110
#define DMA_CHANNEL_7    0b111

#define CLR_MASK_3B      0B111
#define CLR_MASK_2B      0B11

#define DMA_XBURST_INC_Single  0b00
#define DMA_XBURST_INC_4       0b01
#define DMA_XBURST_INC_8       0b10
#define DMA_XBURST_INC_16      0b11

#define CURRENT_TARGET_MEMORY_0   0
#define CURRENT_TARGET_MEMORY_1   1

#define DMA_PRIORITY_LOW  		0b00
#define DMA_PRIORITY_MEDIUM     0b01
#define DMA_PRIORITY_HIGH       0b10
#define DMA_PRIORITY_VERY_HIGH  0b11

#define DMA_PINCOS_LINKED_TO_PSIZE 0
#define DMA_PINCOS_FIXED_TO_4      1

#define DMA_DATA_SIZE_BYTE  		0b00
#define DMA_DATA_SIZE_HALF_WORD     0b01
#define DMA_DATA_SIZE_WORD          0b10

#define DMA_DATA_TRANSFER_PERIPHERAL_TO_MEMORY  	0b00
#define DMA_DATA_TRANSFER_MEMORY_TO_PERIPHERAL      0b01
#define DMA_DATA_TRANSFER_MEMORY_TO_MEMORY          0b10

#define FLOW_CONTROLLER_DMA			 0
#define FLOW_CONTROLLER_PERIPHERAL   1

#define ENABLE   1
#define DISABLE  0

#define FIFO_LEVEL_EMPTY_TO_QUARTER			0B000
#define FIFO_LEVEL_QUARTER_TO_HALF			0B001
#define FIFO_LEVEL_HALF_TO_THREE_QUARTERS	0B010
#define FIFO_LEVEL_THREE_QUARTERS_TO_FULL	0B011
#define FIFO_LEVEL_EMPTY					0B100
#define FIFO_LEVEL_FULL						0B101

/*FIFO Threshold*/
#define FIFO_QUARTER_FULL         0b00
#define FIFO_HALF_FULL            0b01
#define FIFO_THREE_QUARTERS_FULL  0b10
#define FIFO_FULL        		  0b11
/*
 * Options:
 * InterruptFlagName:
 * 	DMA_enuL/HISR_FEIFx,FEIFx: Stream x FIFO error interrupt flag
 *	DMA_enuL/HISR_DMEIFx,DMEIFx: Stream x direct mode error interrupt flag
 *	DMA_enuL/HISR_TEIFx,TEIFx: Stream x transfer error interrupt flag
 *	DMA_enuL/HISR_HTIFx,HTIFx: Stream x half transfer interrupt flag
 *	DMA_enuL/HISR_TCIFx,TCIFx: Stream x transfer complete interrupt flag
 * */
DMA_ErrorStatus_t DMA_getStreamXInterruptFlag(void* DMAx,u32 InterruptFlagName,u8* FlagValue);
/*
 * Options:
 * InterruptFlagName:
 * 	DMA_enuL/HIFCR_CFEIFx,CFEIFx: Stream x clear FIFO error interrupt flag
 *	DMA_enuL/HIFCR_CDMEIFx,CDMEIFx: Stream x clear direct mode error interrupt flag
 *	DMA_enuL/HIFCR_CTEIFx,CTEIFx: Stream x clear transfer error interrupt flag
 *	DMA_enuL/HIFCR_CHTIFx,CHTIFx: Stream x clear half transfer interrupt flag
 *	DMA_enuL/HIFCR_CTCIFx,CTCIFx: Stream x clear transfer complete interrupt flag
 * */
DMA_ErrorStatus_t DMA_clearStreamXInterruptFlag(void* DMAx,u32 InterruptFlagName);

/*NOTE:This Function could be used only if EN is ‘0’
 *Options: DMA_StreamNumber:(0:7)
 *ChannelNumber:
DMA_CHANNEL_0
DMA_CHANNEL_1
DMA_CHANNEL_2
DMA_CHANNEL_3
DMA_CHANNEL_4
DMA_CHANNEL_5
DMA_CHANNEL_6
DMA_CHANNEL_7
 * */
DMA_ErrorStatus_t DMA_selectStreamXChannel(void* DMAx,u8 DMA_StreamNumber,u32 DMA_CHANNEL_x);

/*NOTE:This Function could be used only if EN is ‘0’
 *Options:  DMA_StreamNumber:(0:7)
 *DMA_MBURST_INC_x:
DMA_XBURST_INC_Single
DMA_XBURST_INC_4
DMA_XBURST_INC_8
DMA_XBURST_INC_16
*/
DMA_ErrorStatus_t DMA_setMemoryBurstTransferCfg(void* DMAx,u8 DMA_StreamNumber,u32 DMA_XBURST_INC_x);

/*NOTE:This Function could be used only if EN is ‘0’
 *Options:  DMA_StreamNumber:(0:7)
 *DMA_MBURST_INC_x:
DMA_XBURST_INC_Single
DMA_XBURST_INC_4
DMA_XBURST_INC_8
DMA_XBURST_INC_16
*/
DMA_ErrorStatus_t DMA_setPeripheralBurstTransferCfg(void* DMAx,u8 DMA_StreamNumber,u32 DMA_XBURST_INC_x);

/*NOTE:This Function could be used only if EN is ‘0’
 * Only in double buffer mode
 * Options: DMA_StreamNumber:(0:7)
 *  CurrentTarget:
CURRENT_TARGET_MEMORY_0 :addressed by the DMA_SxM0AR pointer
CURRENT_TARGET_MEMORY_1 :addressed by the DMA_SxM1AR pointer
*/
DMA_ErrorStatus_t DMA_setCurrentTarget(void* DMAx,u8 DMA_StreamNumber,u8 CurrentTarget);
DMA_ErrorStatus_t DMA_getCurrentTarget(void* DMAx,u8 DMA_StreamNumber,u8* CurrentTargetValue);

/*NOTE:This Function could be used only if EN is ‘0’
 * Options: DMA_StreamNumber:(0:7)
 * DMA_enuSxCR_Mode:
 *DMA_enuSxCR_DBM : Double buffer mode :Memory target switched at the end of the DMA transfer
 *DMA_enuSxCR_MINC : Memory increment mode :Memory address pointer is incremented after each data transfer (increment is done according to MSIZE)
 *DMA_enuSxCR_PINC : Peripheral increment mode : Peripheral address pointer is incremented after each data transfer (increment is done according to PSIZE)
 *DMA_enuSxCR_CIRC : : Circular mode : Circular mode enabled
 * */
DMA_ErrorStatus_t DMA_setMode(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_Mode);
/* DMA_enuSxCR_Mode:
 *DMA_enuSxCR_DBM : Double buffer mode : No buffer switching at the end of transfer
 *DMA_enuSxCR_MINC : Memory increment mode : Memory address pointer is fixed
 *DMA_enuSxCR_PINC : Peripheral increment mode : Peripheral address pointer is fixed
 *DMA_enuSxCR_CIRC : Circular mode :  Circular mode disabled
 * */
DMA_ErrorStatus_t DMA_clearMode(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_Mode);

/*NOTE:This Function could be used only if EN is ‘0’
 * Options: DMA_StreamNumber:(0:7)
 * DMA_PRIORITY_X:
 * DMA_PRIORITY_LOW
 * DMA_PRIORITY_MEDIUM
 * DMA_PRIORITY_HIGH
 * DMA_PRIORITY_VERY_HIGH
 */
DMA_ErrorStatus_t DMA_setPriorityLevel(void* DMAx,u8 DMA_StreamNumber,u32 DMA_PRIORITY_X);
/*NOTE:This Function could be used only if EN is ‘0’
 * This Function has no meaning if PINC Mode is Disabled.
 * This bit is forced low by hardware when ( EN = '1') if the direct mode is selected or if PBURST are different from “00”.
 * DMA_PINCOS_LINKED_TO_PSIZE
 * DMA_PINCOS_FIXED_TO_4 */
DMA_ErrorStatus_t DMA_setPeripheralIncrementOffsetSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_PINCOS_X);

/*NOTE:This Function could be used only if EN is ‘0’
 * In direct mode, MSIZE is forced by hardware to the same value as PSIZE as soon as bit EN
= '1'.
 * Options :
 * DMA_DATA_SIZE_X:
 * DMA_DATA_SIZE_BYTE
 * DMA_DATA_SIZE_HALF_WORD
 * DMA_DATA_SIZE_WORD */
DMA_ErrorStatus_t DMA_setMemoryDataSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_SIZE_X);

/*NOTE:This Function could be used only if EN is ‘0’
 * Options :
 * DMA_DATA_SIZE_X:
 * DMA_DATA_SIZE_BYTE
 * DMA_DATA_SIZE_HALF_WORD
 * DMA_DATA_SIZE_WORD */
DMA_ErrorStatus_t DMA_setPeripheralDataSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_SIZE_X);

/*NOTE:This Function could be used only if EN is ‘0’
 * Options:DMA_DATA_TRANSFER_X:
 *DMA_DATA_TRANSFER_PERIPHERAL_TO_MEMORY
 *DMA_DATA_TRANSFER_MEMORY_TO_PERIPHERAL
 *DMA_DATA_TRANSFER_MEMORY_TO_MEMORY      */
DMA_ErrorStatus_t DMA_setDataTransferDirection(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_TRANSFER_X);

/*NOTE:This Function could be used only if EN is ‘0’
 * Options:
 * FLOW_CONTROLLER_X:
 * FLOW_CONTROLLER_DMA
 * FLOW_CONTROLLER_PERIPHERAL*/
DMA_ErrorStatus_t DMA_selectFlowController(void* DMAx,u8 DMA_StreamNumber,u32 FLOW_CONTROLLER_X);
/*Options:
 *DMA_DMA_enuSxCR_IntName:
DMA_enuSxCR_DMEIE, Direct mode error interrupt enable
DMA_enuSxCR_TEIE, Transfer error interrupt enable
DMA_enuSxCR_HTIE, Half transfer interrupt enable
DMA_enuSxCR_TCIE, Transfer complete interrupt
DMA_enuSxFCR_FEIE, FIFO error interrupt enable
 *Interrupt1_State:
ENABLE
DISABLE*/
DMA_ErrorStatus_t DMA_setInterruptState(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_IntName, u8 Interrupt_State);

/*This bit may be cleared by hardware:
– on a DMA end of transfer (stream ready to be configured)
– if a transfer error occurs on the AHB master buses
– when the FIFO threshold on memory AHB port is not compatible with the size of the burst
When this bit is read as 0, the software is allowed to program the Configuration and FIFO
bits registers. It is forbidden to write these registers when the EN bit is read as 1.
Note: Before setting EN bit to '1' to start a new transfer, the event flags corresponding to the
stream in DMA_LISR or DMA_HISR register must be cleared. */
DMA_ErrorStatus_t DMA_setStreamState(void* DMAx,u8 DMA_StreamNumber, u8 Stream_State);

/*NOTE:This Function could be used only if EN is ‘0’
 * Once the transfer has completed, this register can either stay at zero (when the stream is in
normal mode) or be reloaded automatically with the previously programmed value in the
following cases:
– when the stream is configured in Circular mode.
– when the stream is enabled again by setting EN bit to '1'
 * */
DMA_ErrorStatus_t DMA_setNumberOfDataToBeTransferred(void* DMAx,u8 DMA_StreamNumber, u16 NumberOfData);
/* NOTE:This Function could be used only if EN is ‘0’
 * Base address of the peripheral data register from/to which the data will be read/written.*/
DMA_ErrorStatus_t DMA_setPeripheralAddres(void* DMAx,u8 DMA_StreamNumber, void* PeripheralAddress);

/*Base address of Memory area 0 from/to which the data will be read/written.
These bits are write-protected. They can be written only if:
– the stream is disabled (bit EN= '0' in the DMA_SxCR register) or
– the stream is enabled (EN=’1’ in DMA_SxCR register) and bit CT = '1' in the DMA_SxCR register (in Double buffer mode).*/
DMA_ErrorStatus_t DMA_setMemory0Addres(void* DMAx,u8 DMA_StreamNumber, void* Memory0Address);

/*Base address of Memory area 1 from/to which the data will be read/written.
This register is used only for the Double buffer mode.
These bits are write-protected. They can be written only if:
– the stream is disabled (bit EN= '0' in the DMA_SxCR register) or
– the stream is enabled (EN=’1’ in DMA_SxCR register) and bit CT = '0' in the DMA_SxCR register.*/
DMA_ErrorStatus_t DMA_setMemory1Addres(void* DMAx,u8 DMA_StreamNumber,void* Memory1Address);
/*
 * Options:
 * FIFO_LEVEL_X:
 * FIFO_LEVEL_EMPTY_TO_QUARTER			0B000
 * FIFO_LEVEL_QUARTER_TO_HALF			0B001
 * FIFO_LEVEL_HALF_TO_THREE_QUARTERS	0B010
 * FIFO_LEVEL_THREE_QUARTERS_TO_FULL	0B011
 * FIFO_LEVEL_EMPTY						0B100
 * FIFO_LEVEL_FULL						0B101
 * */
DMA_ErrorStatus_t DMA_getFIFOStatus(void* DMAx,u8 DMA_StreamNumber, u32* FIFO_LEVEL_X);

/*NOTE:This Function could be used only if EN is ‘0’
 * This bit is set by hardware if the memory-to-memory mode is selected (DIR bit in
DMA_SxCR are “10”) and the EN bit in the DMA_SxCR register is ‘1’ because the direct
mode is not allowed in the memory-to-memory configuration.*/
DMA_ErrorStatus_t DMA_setDirectModeStatus(void* DMAx,u8 DMA_StreamNumber, u8 DirectModeStatus);
/*NOTE:This Function could be used only if EN is ‘0’
 *
 * FIFO_x_FULL:
 * FIFO_QUARTER_FULL
 * FIFO_HALF_FULL
 * FIFO_THREE_QUARTERS_FULL
 * FIFO_FULL
 * */
DMA_ErrorStatus_t DMA_selectFIFOThreshold(void* DMAx,u8 DMA_StreamNumber, u8 FIFO_x_FULL);


//DMA_ErrorStatus_t DMA_setCallBack(void* DMAx,u8 DMA_StreamNumber, void(*DMA_CBF_MAIN)(void));

DMA_ErrorStatus_t DMA2_Stream2_setCallBack( void(* DMA2_Stream2_CBF_MAIN)(void) );
DMA_ErrorStatus_t DMA2_Stream7_setCallBack( void(* DMA2_Stream7_CBF_MAIN)(void) );

void DMA_Init(void* DMAx,u8 DMA_StreamNumber);


void DMA2_Stream2_RX(void);
void DMA2_Stream7_TX(void);






#endif /* __DMA_H__ */
