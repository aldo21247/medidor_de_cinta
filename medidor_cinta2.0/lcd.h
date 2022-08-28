#define  F_CPU 1000000UL

#include <util/delay.h>

// Manda el pulso de habilitación sin alterar otras terminales
void LCD_pulso_E();

// Escribe una instrucción de 4 bits, recibida en el nibble inferior
void LCD_write_inst4(uint8_t  inst);

// Escribe una instrucción de 8 bits
void LCD_write_inst8(uint8_t  ints);

// Escrible un dato de 8 bits
void LCD_write_data( uint8_t  dat_8b);

// Inicializa al LCD
void LCD_reset();

// Funcion para la limpieza del display
void LCD_clear();

// Ubica al cursor, el nibble alto indica el renglon, el bajo la columna
void LCD_cursor(uint8_t   pos);
void LCDGotoXY(uint8_t x, uint8_t y);
void Lcd_Chr(uint8_t x, uint8_t y,uint8_t  dat_8b);
// Escrible una cadena, supone un display de 2 renglones y 16 columnas
void LCD_write_cad(uint8_t x, uint8_t y,char cad[],uint8_t z );
void distancia();
void LcdFloat(const unsigned char fil,unsigned char col, float num, const unsigned char dec);
void PantallaLCD();