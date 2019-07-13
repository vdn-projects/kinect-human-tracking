#include <stdlib.h>
#include <ctype.h>
#include "lcd.h"

void lcd_init(){
	unsigned char i;

	ANS1 = 0;
	ANS2 = 0;
	ANS3 = 0;

	LCD_EN_TRIS = 0;
	LCD_RS_TRIS = 0;
	LCD_RW_TRIS = 0;
	LCD_DATA4_TRIS = 0;
	LCD_DATA5_TRIS = 0;
	LCD_DATA6_TRIS = 0;
	LCD_DATA7_TRIS = 0;
	LCD_EN = 0;
	LCD_RS = 0;
	LCD_RW = 0;

	__delay_ms(100);				// delay for power on
	
	// reset LCD
	lcd_put_byte(0,0x30);
	__delay_ms(50);
	lcd_put_byte(0,0x30);
	__delay_ms(50);
	lcd_put_byte(0,0x32);
	__delay_ms(100);				// delay for LCD reset
	__delay_ms(100);				// delay for LCD reset
	__delay_ms(100);				// delay for LCD reset
	
	while(lcd_busy());
	lcd_put_byte(0,FOUR_BIT & LINES_5X7);			// Set LCD type
	while(lcd_busy());
	
	lcd_put_byte(0,DOFF&CURSOR_OFF&BLINK_OFF);		// display off
	while(lcd_busy());
	lcd_put_byte(0,DON&CURSOR_OFF&BLINK_OFF);		// display on
	while(lcd_busy());
	
	lcd_put_byte(0,0x01);							// clear display and move cursor to home
	while(lcd_busy());
	lcd_put_byte(0,SHIFT_CUR_LEFT);				// cursor shift mode
	while(lcd_busy());
	lcd_put_byte(0,0x01);							// clear display and move cursor to home
	while(lcd_busy());
}
unsigned char lcd_busy()
{
	unsigned char busy;
	
	LCD_DATA4_TRIS = 1;
	LCD_DATA5_TRIS = 1;
	LCD_DATA6_TRIS = 1;
	LCD_DATA7_TRIS = 1;
	
	LCD_RW = 1;
	LCD_RS = 0;
	__delay_us(20);
	LCD_EN = 1;
	__delay_us(20);
	
	busy = LCD_DATA7;
	
	LCD_EN = 0;
	__delay_us(20);
	LCD_EN = 1;
	__delay_us(20);
	LCD_EN = 0;

	
	return busy;
}
void lcd_clear()
{
	lcd_put_byte(0,CLEAR);		// CLEAR command
	while(lcd_busy());	
}
unsigned char lcd_get_byte(unsigned char rs)
{
	BYTE_VAL b;
	
	LCD_DATA4_TRIS = 1;
	LCD_DATA5_TRIS = 1;
	LCD_DATA6_TRIS = 1;
	LCD_DATA7_TRIS = 1;
	
	LCD_RW = 1;
	LCD_RS = 0;
	if(rs) LCD_RS = 1;
	__delay_us(20);
	LCD_EN = 1;
	__delay_us(20);
	
	b.bits.b7 = LCD_DATA7;
	b.bits.b6 = LCD_DATA6;
	b.bits.b5 = LCD_DATA5;
	b.bits.b4 = LCD_DATA4;
	
	LCD_EN = 0;
	__delay_us(20);
	LCD_EN = 1;
	__delay_us(20);
	b.bits.b3 = LCD_DATA7;
	b.bits.b2 = LCD_DATA6;
	b.bits.b1 = LCD_DATA5;
	b.bits.b0 = LCD_DATA4;
	LCD_EN = 0;
	
	return b.Val;
}
void lcd_put_byte(unsigned char rs, unsigned char b)
{
	BYTE_VAL temp;
	
	LCD_DATA4_TRIS = 0;
	LCD_DATA5_TRIS = 0;
	LCD_DATA6_TRIS = 0;
	LCD_DATA7_TRIS = 0;
	
	LCD_RS = 0;
	if(rs) LCD_RS = 1;
	
	__delay_us(20);
	LCD_RW = 0;
	__delay_us(20);
	LCD_EN = 0;
	
	temp.Val = b;
	
	// send the high nibble
	LCD_DATA4 = temp.bits.b4;
	LCD_DATA5 = temp.bits.b5;
	LCD_DATA6 = temp.bits.b6;
	LCD_DATA7 = temp.bits.b7;
	__delay_us(20);
	LCD_EN =  1;
	__delay_us(20);
	LCD_EN = 0;
	// send the low nibble
	LCD_DATA4 = temp.bits.b0;
	LCD_DATA5 = temp.bits.b1;
	LCD_DATA6 = temp.bits.b2;
	LCD_DATA7 = temp.bits.b3;
	__delay_us(20);
	LCD_EN =  1;
	__delay_us(20);
	LCD_EN = 0;
}
void lcd_putc(char c){
	switch(c){
		case '\f':
			lcd_put_byte(0, 1);
			while(lcd_busy());
			break;
		case '\n':
			lcd_gotoxy(0, 1);
			break;
		default:
			if(isprint(c)){
				lcd_put_byte(1, c);
				while(lcd_busy());
			}
			break;
	}
}

void lcd_gotoxy(unsigned char col, unsigned char row)
{
	unsigned char address;
	
	if(row!=0)
		address=0x40;
	else
		address=0;
	
	address += col;
	lcd_put_byte(0,0x80|address);
	while(lcd_busy());
}
void lcd_puts(const char* s)
{
	while(*s){
		lcd_putc(*s++);
	}
}

