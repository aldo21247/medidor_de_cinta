/*
 * medidor_cinta2.0.cpp
 *
 * Created: 12/08/2021 02:40:20 p. m.
 * Author : Aldo Zepeda
 */ 

#include <avr/io.h>
#include "lcd.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
#define  P_LCD  PORTC
float perimetroRueda=1.592;
float distRecorrida=0;
float costo=0;
int estadoActual1=0;
int estadoActual2=0;
int estadoUltimo=0;
int contador=0;
int main(void)
    
{   DDRC=0XfF;
	DDRB |=(1<<2);
	DDRD&=~(1<<3);
	LCD_reset();
    
    
    /* Replace with your application code */
   
    while (1) 
    {
		estadoActual1=PIND &0x08;
		_delay_ms(2);
	    estadoActual2=PIND &0x08;
		
		if (estadoActual1 == estadoActual2) {
			if (estadoActual1 != estadoUltimo){
				
				if (estadoActual1 != 0){
					distancia();
					
					
					contador = contador + 1;
					
				}
				else{
					PORTB|=(0b00000100);
				}
			}
		}
		 estadoUltimo= estadoActual1;
      
	    
    
	
	PantallaLCD();
}
}
	// Puerto donde se conectará el LCD



// Conexión del LCD: Interfaz de 4 bits
// D4 - P_LCD_0
// D5 - P_LCD_1
// D6 - P_LCD_2
// D7 - P_LCD_3
// E  - P_LCD_4
// RS - P_LCD_5
// RW - debe conectarse a Tierra

// Manda el pulso de habilitación sin alterar otras terminales
void LCD_pulso_E()
{
	P_LCD = P_LCD | 0x10;
	P_LCD = P_LCD & 0xEF;
}

// Escribe una instrucción de 4 bits, recibida en el nibble inferior
void LCD_write_inst4(uint8_t  inst)
{
	P_LCD = inst & 0x0F;        // Rs =  0
	LCD_pulso_E();
}

// Escribe una instrucción de 8 bits
void LCD_write_inst8(uint8_t   inst)
{
	uint8_t   temp;

	temp = (inst & 0xF0) >> 4;
	LCD_write_inst4(temp);      // Primero el nibble alto

	temp = inst & 0x0F;
	LCD_write_inst4(temp);      // Después el nibble bajo

	_delay_us(40);
}

// Escrible un dato de 8 bits
void LCD_write_data(uint8_t dat_8b)
{
	uint8_t temp;
   
	temp = (dat_8b & 0xF0) >> 4;	// PARTE ALTA
	P_LCD = temp | 0x20; 			// RS = 1
	LCD_pulso_E();

	temp = dat_8b & 0x0F; 			// PARTE BAJA
	P_LCD = temp | 0x20;  			// RS = 1
	LCD_pulso_E();

	_delay_us(40);
}

// Inicializa al LCD
void LCD_reset()
{
	_delay_ms(15);
	LCD_write_inst4(0x03);      // Configura la función del Display
	// La interfaz aún es de 8 bits
	_delay_ms(4.1);
	LCD_write_inst4(0x03);      // Configura la función del Display
	// La interfaz aún es de 8 bits
	_delay_us(100);
	LCD_write_inst4(0x03);      // Configura la función del Display
	_delay_us(40);              // La interfaz aún es de 8 bits

	LCD_write_inst4(0x02);      // Configura la función del Display
	_delay_us(40);              // Define la interfaz de 4 bits

	LCD_write_inst8(0X28);      // Configura la función del Display
	// Dos líneas y 5x7 puntos
	LCD_write_inst8(0X0C);      // Encendido del display

	LCD_clear();                // Limpieza del display

	LCD_write_inst8(0X06);      //  Ajuste de entrada de datos
	// Autoincremento del contador
	// y sin desplazamiento
}

// Funcion para la limpieza del display
void LCD_clear()
{
	LCD_write_inst8(0X01);
	_delay_ms(2);
}

// Ubica al cursor, el nibble alto indica el renglon, el bajo la columna
void LCD_cursor(uint8_t   pos)
{
	uint8_t  col;
	col = pos & 0X0F;
	if((pos & 0XF0) == 0)
	{
		col = col | 0X80;
		LCD_write_inst8(col);
	}
	else
	{
		col = col | 0XC0;
		LCD_write_inst8(col);
	}
}
void LCDGotoXY(uint8_t x, uint8_t y)
{
if(x!=1){
	switch(y)
	{
		case 0:LCD_cursor(0x00);
		break;
		case 1:LCD_cursor(0x01);
		break;
		case 2:LCD_cursor(0x02);
		break;
		case 3:LCD_cursor(0x03);
		break;
		case 4:LCD_cursor(0x04);
		break;
		case 5:LCD_cursor(0x05);
		break;
		case 6:LCD_cursor(0x06);
		break;
		case 7:LCD_cursor(0x07);
		break;
		case 8:LCD_cursor(0x08);
		break;
		case 9:LCD_cursor(0x09);
		break;
		case 10:LCD_cursor(0x0A);
		break;
		case 11:LCD_cursor(0x0B);
		break;
		case 12:LCD_cursor(0x0C);
		break;
		case 13:LCD_cursor(0x0D);
		break;
		default:LCD_cursor(0x0E);
	}
}
else{
	switch(y)
	{
		case 0:LCD_cursor(0x10);
		break;
		case 1:LCD_cursor(0x11);
		break;
		case 2:LCD_cursor(0x12);
		break;
		case 3:LCD_cursor(0x13);
		break;
		case 4:LCD_cursor(0x14);
		break;
		case 5:LCD_cursor(0x15);
		break;
		case 6:LCD_cursor(0x16);
		break;
		case 7:LCD_cursor(0x17);
		break;
		case 8:LCD_cursor(0x18);
		break;
		case 9:LCD_cursor(0x19);
		break;
		case 10:LCD_cursor(0x1A);
		break;
		case 11:LCD_cursor(0x1B);
		break;
		case 12:LCD_cursor(0x1C);
		break;
		case 13:LCD_cursor(0x1D);
		break;
		default:LCD_cursor(0x1E);		
		
}

	
	
	
}
}
// Escribe una cadena, supone un display de 2 renglones y 16 columnas
void LCD_write_cad(uint8_t x, uint8_t y,char  cad[],uint8_t z)
{
	uint8_t  i;


	LCDGotoXY(x,y);

	for(i=0; i<z; i++)
	{
		LCD_write_data((float) cad[i]);
		if(i==z)
		LCD_cursor(0X10);
	}
}
void Lcd_Chr(uint8_t r, uint8_t s,uint8_t  letra){
	LCDGotoXY( r,s);
	LCD_write_data(letra);
}

void LcdOut(const unsigned char fil,unsigned char col,const unsigned char* texto){
	while(*texto)
	Lcd_Chr(fil,col++,*texto++);
}
void LcdFloat(const unsigned char fil,unsigned char col, float num, const unsigned char dec){
	unsigned char x=0;
	unsigned char nent=0;
	unsigned long ent=num;
	float decimales=num;
	float resultado=0;
	unsigned long rdec=0;
	unsigned char texto[10];
	for(x=0;ent>0;x++){
		ent/=10;
		nent++;
	}
	if(nent==0) nent=1;
	ent=num;
	resultado=decimales-ent;
	for(x=1;x<=dec;x++)
	resultado*=10;
	for(x=0;x<nent;x++){
		texto[x]=ent%10;
		ent/=10;
	}
	for(x=nent;x>0;x--)
	Lcd_Chr(fil,col++,texto[x-1]+48);
	LCD_write_data(46);
	col++;
	rdec=resultado;
	for(x=0;x<dec;x++){
		texto[x]=rdec%10;
		rdec/=10;
	}
	for(x=dec;x>0;x--)
	Lcd_Chr(fil,col++,texto[x-1]+48);
}
void distancia(){
	distRecorrida=perimetroRueda*contador;
	
	PORTB&=~(0b00000100);
	
	
	costo=1.5*distRecorrida;
	
}
 void PantallaLCD(){
	 
	 LCD_write_data(0x24);
	 LcdFloat(0,1,costo, 2);
	 
	LCD_write_cad(0,8,"ING.ALDO",8);
    LCD_write_cad(1,0,"D=",2);
	LcdFloat(1,2,distRecorrida, 2);
	LCD_write_cad(1,10,"METROS",6);	 
		 
	 
	 
	 return;
 }