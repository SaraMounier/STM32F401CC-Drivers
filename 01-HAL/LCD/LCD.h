/*************************************************************
 * 
 * Filename: LCD.h
 * Description: Header (interface) file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LCD_H__
#define __LCD_H__

#include "STD_TYPES.h"
/*Display Control Instructions*/
/*Clear Display : 0b0000000001
The execution of clear display instruction sets entry mode to increment mode (I/D = 1).*/
#define LCD_CLR			0x01 

/*Return Home: 000000001-
Sets the DD RAM address “00H” in address counter. Return display to its original position
if it was shifted. DD RAM contents do not change. The cursor or the blink moves to the
upper left end of the display. Contents of DD RAM remain unchanged.
*/
#define LCD_HOME		0X02

/* Entry Mode Set: 00 0000 0001 I/D SH
Sets cursor move direction and Enable the shift of entire display.
These operations are performed during data write and read.
I/D: Increases (I/D = 1) or decreases (ID = 0) the DD RAM address by 1 when a character
code is written into or read from the DD RAM.
S = 0 : No Display Shift operation
*/
#define LCD_ENTRYMOE_NOSHIFT_INC 0x06
#define LCD_ENTRYMOE_SHIFT_INC 0x07
#define LCD_ENTRYMOE_NOSHIFT_DEC 0x04
#define LCD_ENTRYMOE_SHIFT_DEC 0x05
/*Display ON/OFF Control: 00 0000 1DCB
Set ON/OFF of entire display (D),cursor ON/OFF(C), and blinking of cursor position character(B)
. The cursor is displayed on the 8th line when 5x7 dots character font has been selected.
*/
#define LCD_OFF 0X08
#define LCD_ON_CURSOR_ON_BLINKING_ON 0X0f
#define LCD_ON_CURSOR_ON_BLINKING_OFF 0X0E
#define LCD_ON_CURSOR_OFF 0X0C

/*Cursor or Display Shift: 00 0001 S/C R/L --
Moves cursor and shifts display without changing DDRAM contents.*/
#define SHIFT_CURSOR_LEFT 0X10
#define SHIFT_CURSOR_RIGHT 0X14
#define SHIFT_DISPLAY_LEFT_CURSOR_FOLLOWS 0X18
#define SHIFT_DISPLAY_RIGHT_CURSOR_FOLLOWS 0X1C
/*Function Set:00 001DL NF--
Sets the interface data length, the number of lines, and character font.
DL:data length 4bit: D=0, 8 BITS: D=1
 When the 4-bit length is selected, data must be sent or received twice.
 N:Number of lines N = 0 : 1 line display (1/8 duty), N = 1 : 2 line display (1/16 duty)
 F: Sets character font. F = 0 : 5 x 7 dots F = 1 : 5 x 10 dots */

#define _4BITS_1LINE_5x7FONT  0X20
#define _4BITS_1LINE_5x10FONT 0X24
#define _4BITS_2LINE_5x7FONT  0X28
#define _4BITS_2LINE_5x10FONT 0X2C

#define _8BITS_1LINE_5x7FONT  0X30
#define _8BITS_1LINE_5x10FONT 0X34
#define _8BITS_2LINE_5x7FONT  0X38
#define _8BITS_2LINE_5x10FONT  0X3C


/*Select your Initialization*/
#define SELECTED_ENTRY_MODE_SET            LCD_ENTRYMOE_NOSHIFT_INC
#define SELECTED_FUNCTION_SET              _8BITS_2LINE_5x7FONT
#define SELECTED_CURSOR_DISPLAY_SHIFT 		SHIFT_CURSOR_RIGHT
#define SELECTED_DISPLAY_ON_OFF_CONTROL    LCD_ON_CURSOR_ON_BLINKING_ON


/*Set CGRAM Address: 00 01AC5AC4 AC3AC2AC1
Sets the CG RAM address to the address counter. Data is then written/read to/from the CG RAM.*/
#define MASK_CGRAM 0X40

/*Set DDRAM Address: 00 1AC6AC5AC4 AC3AC2AC1
Sets the DD RAM address to the address counter. Data is then written/read to/from the DD RAM
Sets the DD RAM address to the address counter. Data is then written/read to/from the DD RAM.
When in 1-line display mode (N = 0), DD RAM address is from “00H” to “4FH”.
When in 2-line display mode (N = 1), DD RAM address corresponding to 1st line and 3rd
line of the display is from “00H” to “27H”; the address corresponding to 2nd and 4th line of
the display is from “40H” to “67H”.*/

#define MASK_DDRAM 0X80
/*Read Busy Flag & Address: 01 BFAC6AC5AC4 AC3AC2AC1
Reads busy flag (BF) indicating internal operation is being performed and reads address counter contents
BF = 1 indicates that internal operation is in progress and the next instruction will not be accepted until BF is set
to “0”. The BF status should be checked before each write operation. At the same time the value of the address counter is read out.
The address counter is used by both CG and DDRAM and its value is determined by the previous instruction*/


/*Write Data to CG or DD RAM : 10 D7D6D5D4D3D2D1D0
 After a write the address is automatically increased or decreased by 1, according to the entry mode. The entry mode
 also determines display shift.*/
/*Read Data from CG or DD RAM : : 10 D7D6D5D4D3D2D1D0 
The “address set” instruction need not be executed just before the “read”
instruction when shifting the cursor by cursor shift instruction (when reading DD RAM).
The cursor shift instruction operation is the same as that of the DD RAM address set
instruction.

The conditions for correct data read out are: (a) Execute either the address set instruction
or cursor shift instruction (only with DD RAM) or (b) The execution of the “read data”
instruction from the second time when the read instruction is performed multiple times in
serial.*/
#define FIRST_LINE  0x80
#define SECOND_LINE 0xC0


#define LCD_POSITION01  00
#define LCD_POSITION02  01
#define LCD_POSITION03  02
#define LCD_POSITION04  03
#define LCD_POSITION05  04
#define LCD_POSITION06  05
#define LCD_POSITION07  06
#define LCD_POSITION08  07
#define LCD_POSITION09  8
#define LCD_POSITION10  9
#define LCD_POSITION11  10
#define LCD_POSITION12  11
#define LCD_POSITION13  12
#define LCD_POSITION14  13
#define LCD_POSITION15  14
#define LCD_POSITION16  15

#define LCD_SPECIALCHAR1  0
#define LCD_SPECIALCHAR2  1
#define LCD_SPECIALCHAR3  2
#define LCD_SPECIALCHAR4  3
#define LCD_SPECIALCHAR5  4
#define LCD_SPECIALCHAR6  5
#define LCD_SPECIALCHAR7  6
#define LCD_SPECIALCHAR8  7


typedef enum 
{
//LCD_enuOK,
//LCD_enuNOK,
LCD_enuIdle,
LCD_enuBusy,
LCD_enuNotInitialized,
LCD_enuInvalidParameter,
LCD_enuNullPtr,
}LCD_enuErrorStatus;

typedef struct
{
	char* Word;
	u8 length;
	u8 X_Position;
	u8 Y_Position;
	u8 Char_Index;
}LCD_strInputString_t;

typedef struct
{
	u32 Number;
	u8 length;
	u8 X_Position;
	u8 Y_Position;
}LCD_strInputNumber_t;

typedef struct
{
	u8 command;

}LCD_strCommand_t;

typedef enum
{
	Req_Idle,/*new not used yet*/
	Req_InitializeLCD,
	Req_SendCommand,
	Req_ClearChar,
	Req_WriteString,
	Req_WriteNumber,
}LCD_RequiredTask_t;

void LCD_ConfigurePins(void);
void LCD_vidInit(void);
LCD_enuErrorStatus LCD_WriteString(u8 * string,u8 length,u8 LCD_X_Position,u8 LCD_Y_Position);
void Req_Write_String_Handle(void);
LCD_enuErrorStatus LCD_SendCommand(u8 LCD_Command );
void Req_Send_Command_Handle(void);
LCD_enuErrorStatus LCD_WriteNumber (u32 u32Number,u8 LCD_X_Position,u8 LCD_Y_Position);
void Req_Write_Number_Handle(void);
void LCD_vidTask(void);
void task1_lcd(void);
void task_toggle(void);

/*
LCD_enuErrorStatus LCD_enuSendData    (u8 Copy_u8Data);
LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command);
LCD_enuErrorStatus LCD_enuGotoXY      (u8 Copy_u8XPos, u8 Copy_u8YPos);
LCD_enuErrorStatus LCD_enuWriteSpecialPattern  (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);
LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString);
*/
#endif /* __LCD_H__ */
