
#include <xc.h>
#include "keypad.h"
#pragma config FOSC = INTIO7    
#define _XTAL_FREQ 8000000

#define lcd PORTD

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

#define C1 PORTBbits.RB0
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB2

#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7

void lcd_lat(){
    EN=1;
    __delay_ms(10);
    EN=0;
}

void lcd_cmd(unsigned char command){
    lcd = command;
    RS=0;
    RW=0;
    lcd_lat();
}

void lcd_data(unsigned char data){
    lcd = data;
    RS=1;
    RW=0;
    lcd_lat();
}


void lcd_string(unsigned char *strng)
{
    while(*strng != 0)              
        lcd_data(*strng++);          //Sends data to LCD and then increment
}


void lcd_int(){
    lcd_cmd(0x38);              //8-bit mode, 2 lines, 5x7 dots matrix
    lcd_cmd(0x0E);              //Cursor Blinking
    lcd_cmd(0x01);              //Clear LCD
    lcd_cmd(0x06);              //Increment Cursor
    lcd_cmd(0x80); 
}

void keypadC1(){
    
    C1=1;
    C2=0;
    C3=0;
    
  if(R1==1){
        lcd_data('1');
    while(R1==1);
    }
    if(R2==1){
        lcd_data('4');
    while(R2==1);
    }
    if(R3==1){
        lcd_data('7');
    while(R3==1);
    }
    if(R4==1){
        lcd_data('*');
    while(R4==1);
    }}
    
   void keypadC2(){ 
    C1=0;
    C2=1;
    C3=0;
    
    
    if(R1==1){
        lcd_data('2');
    while(R1==1);
    }
    if(R2==1){
        lcd_data('5');
    while(R2==1);
    }
    if(R3==1){
        lcd_data('8');
    while(R3==1);
    }
    if(R4==1){
        lcd_data('0');
    while(R4==1);
    }}
   void keypadC3(){
    
    C1=0;
    C2=0;
    C3=1;
    
    
    if(R1==1){
        lcd_data('3');
    while(R1==1);
    }
    if(R2==1){
        lcd_data('6');
    while(R2==1);
    }
    if(R3==1){
        lcd_data('9');
    while(R3==1);
    }
    if(R4==1){
        lcd_data('#');
    while(R4==1);
    }
   }

void main() {
    TRISB = 0xF0;
    ANSELD = 0x00;
    TRISD = 0x00;
    ANSELC &= 0xF8;
    TRISC &= 0xF8;
    lcd_int();
    lcd_cmd(0x80);
    lcd_string("KEYPAD:");
    lcd_cmd(0xC0);
  while(1){
  keypadC1();
   keypadC2();
    keypadC3();
  }
          
}
