/*
 * lcd.cc
 *
 * Objekt zur grundlegenden Ansteuerung des LCDs der Chronos-Uhr
 *
 * Kann im Augenblick nur initialisieren (im Konstruktor) und
 * alle Segmente ausschalten.
 */

#include <msp430.h>
#include "machine/lcd.h"

unsigned char digitArr[] = {
  0b11110101,
  0b01100000,
  0b10110110,
  0b11110010,
  0b01100011,
  0b11010011,
  0b11010111,
  0b01110000,
  0b11110111,
  0b11110011
};

LCD LCD::lcd; // Singleton Instanz

LCD::LCD() {
  // Display-Speicher loeschen
  LCDBMEMCTL |= LCDCLRBM | LCDCLRM;

  // LCD_FREQ = ACLK/16/8 = 256Hz
  // Framefrequenz = 256Hz/4 = 64Hz, LCD mux 4, LCD on
  LCDBCTL0 = LCDDIV_15 | LCDPRE__8 | LCD4MUX | LCDON;

  // Blinkfrequenz = ACLK/8/4096 = 1Hz
  LCDBBLKCTL = LCDBLKPRE0 | LCDBLKPRE1 |
               LCDBLKDIV0 | LCDBLKDIV1 | LCDBLKDIV2 | LCDBLKMOD0;

  // I/O to COM outputs
  P5SEL |= (BIT5 | BIT6 | BIT7);
  P5DIR |= (BIT5 | BIT6 | BIT7);

  // LCD-Ausgabe aktivieren
  LCDBPCTL0 = 0xFFFF;
  LCDBPCTL1 = 0xFF;
}

void LCD::clear() { LCDBMEMCTL |= LCDCLRBM | LCDCLRM; }


// Hier muesst ihr selbst Code ergaenzen, beispielsweise:
void LCD::show_number(long int number, bool upper_line) {
  char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
  char*addr ;
  int  offset =0x20 ,  x=1;
  addr = LCD_BASE + offset + x ;
  *addr = 0b00001000;
}


void LCD::show_digit(unsigned int digit, unsigned int pos, bool upper_line){
  char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
  char*addr ;
  int  offset =0x20;
  unsigned int  x=pos;
  unsigned char lcd_digit = digitArr[digit];


  if(!upper_line){
    x=12-x;

    //Hier wird lower -> upper geshiftet
    unsigned char temp1 = lcd_digit & 0b11110000;
    unsigned char temp2 = lcd_digit & 0b00001111;
    temp1 = temp1 >> 4;
    temp2 = temp2 << 4;
    lcd_digit = temp1 | temp2;

  } else {
    if(x==4){
      x++;
    }
  }

  //Fehlerüberprüfung (Mit momentan ḱlarer Fehlermeldung)
if (x > 11){
  x = 4;
}

  addr = LCD_BASE + offset + x ;
  *addr = lcd_digit;

 }

void LCD::show_char(const char letter, unsigned int pos, bool upper_line){

}

void LCD::show_string(const char *text, bool upper_line){

}
