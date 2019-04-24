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

//0-1 Array für Segmentbelegung
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

//Alphabet A-Z Segmentbelegung
unsigned char charArr[] = {
  0b01110111,
  0b11000111,
  0b10010101,
  0b11100110,
  0b10010111,
  0b00010111,
  0b11010101,
  0b01000111,
  0b00000101,
  0b11100100,
  0b01010111,
  0b10000101,
  0b01010110,
  0b01000110,
  0b11000110,
  0b00110111,
  0b10110011,
  0b00000110,
  0b11010011,
  0b10000111,
  0b11100101,
  0b11000100,
  0b10100011,
  0b01100111,
  0b11100011,
  0b10110100,
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
  /*   char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
    char*addr ;
    int  offset =0x20;
    unsigned int  x=pos;
    unsigned char lcd_digit = digitArr[digit];

    addr = LCD_BASE + offset + x ;
    *addr = lcd_char;
  */
}



void LCD::show_digit(unsigned int digit, unsigned int pos, bool upper_line) {
  char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
  char*addr ;
  int  offset = 0x20;
  unsigned int  x = pos;
  unsigned char lcd_digit = digitArr[digit];


  if (!upper_line) {
    x = 12 - x;

    //Hier wird lower -> upper geshiftet
    unsigned char temp1 = lcd_digit & 0b11110000;
    unsigned char temp2 = lcd_digit & 0b00001111;
    temp1 = temp1 >> 4;
    temp2 = temp2 << 4;
    lcd_digit = temp1 | temp2;

  } else {
    if (x == 4) {
      x++;
    }
  }

//Fehlerüberprüfung (Mit momentan ḱlarer Fehlermeldung)
  if (x > 11) {
    x = 4;
  }

  addr = LCD_BASE + offset + x ;
  *addr = lcd_digit;

}

//Funktion zur Buchstabenanzeige
void LCD::show_char(const char letter, unsigned int pos, bool upper_line) {
  char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
  char*addr ;
  int  offset = 0x20;
  unsigned int  x = pos;
  unsigned int ascii_int = (int)letter;
  //Behandlung von Groß- und Kleinbuchstaben (untersch. Ascii-Wert)
  if (ascii_int > 90) {
    ascii_int = (int)letter - 97;
  }
  else {
    ascii_int = (int)letter - 65;
  }
  unsigned char lcd_char = charArr[ascii_int];

  if (!upper_line) {
    x = 12 - x;

    //Hier wird lower -> upper geshiftet
    unsigned char temp1 = lcd_char & 0b11110000;
    unsigned char temp2 = lcd_char & 0b00001111;
    temp1 = temp1 >> 4;
    temp2 = temp2 << 4;
    lcd_char = temp1 | temp2;

  } else {
    if (x == 4) {
      x++;
    }
  }

//Fehlerüberprüfung (Mit momentan ḱlarer Fehlermeldung)
  if (x > 11) {
    x = 4;
  }

  addr = LCD_BASE + offset + x ;
  *addr = lcd_char;

}

void LCD::show_string(const char *text, bool upper_line) {

}

