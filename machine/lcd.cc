/*
 * lcd.cc
 *
 *Autoren: Dominik Jülich, Eduard Rempel, Frederik Schierbaum
 *
 * Objekt zur grundlegenden Ansteuerung des LCDs der Chronos-Uhr
 *
 * Aufgaben sind funktionabel.
 */

#include <msp430.h>
#include "machine/lcd.h"

//Sonderzeichen Array zurzeit nur Minus und Leerzeichen
unsigned char symbolArr[] = {
  //Leerzeichen als Unterstrich dargestellt
  0b10000000,
  //Minus Zeichen
  0b00000010
};

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

unsigned char LCD::switch_nibbles(unsigned char input) {
  unsigned char temp1 = input & 0b11110000;
  unsigned char temp2 = input & 0b00001111;
  temp1 = temp1 >> 4;
  temp2 = temp2 << 4;
  return temp1 | temp2;
}

//Nimmt Bytemaske für 7-Segment Anzeige entgegen und mapped es auf die jeweilige Position
void LCD::output (unsigned char input, unsigned int pos, bool upper_line) {
  char*LCD_BASE = reinterpret_cast <char*>(0x0a00) ;
  int offset = 0x20;
  unsigned char symbol = input;

  unsigned int  x = pos;

  if (!upper_line) {
    x = 12 - x;

    //Hier wird lower -> upper geshiftet
    symbol = switch_nibbles(symbol);

  } else {
    if (x == 4) {
      x++;
    }
  }

  //Fehlerüberprüfung (Mit momentan ḱlarer Fehlermeldung)
  if (x > 11) {
    x = 4;
  }

  char*addr = LCD_BASE + offset + x;
  *addr = symbol;
}




// Hier muesst ihr selbst Code ergaenzen, beispielsweise:
void LCD::show_number(long int number, bool upper_line) {
  //Eingabenprüfung:
  if (upper_line) {
    if (number < -999 || number > 9999) {
      for (int i = 1; i < 5; i++) {
        output(symbolArr[1], i, upper_line);
      }
      return;
    }
  } else {
    if (number < -9999 || number > 99999) {
      for (int i = 1; i < 6; i++) {
        output(symbolArr[1], i, upper_line);
      }
      return;
    }
  }

  long int temp = number;
  //Maximale Länge des Arrays festlegen
  int max_digits = upper_line ? 4 : 5;
  unsigned int digits[max_digits];

  //Vorzeichen abfragen
  bool negative = false;
  if (number < 0) {
    negative = true;
    temp *= -1;
  }


  //Zahl in einzelne Stellen aufteilen
  int stop = 0;
  for (int i = max_digits - 1; i >= 0; i--) {
    digits[i] = temp % 10;


    //Führende Nullen entfernen und Anfang der Zahl merken
    if (temp == 0) {
      if(stop==0){
        stop = i;
      }

      output(0b00000000, i+1, upper_line);
    }else {
        show_digit(digits[i], i + 1, upper_line);
    }

     temp /= 10;
  }



  if (negative) {
    output(symbolArr[1], stop+1, upper_line);
  }

}



void LCD::show_digit(unsigned int digit, unsigned int pos, bool upper_line) {
  //Eingabenprüfung
  if (digit > 9) {
    output(symbolArr[1], pos, upper_line);
    return;
  }

  //Ausgabe auf LCD
  output(digitArr[digit], pos, upper_line);
}

//Funktion zur Buchstabenanzeige
void LCD::show_char(const char letter, unsigned int pos, bool upper_line) {
  unsigned int ascii_int = (int)letter;
  //Behandlung von Groß- und Kleinbuchstaben (untersch. Ascii-Wert)
  if (ascii_int > 90) {
    ascii_int -= 97;
  }
  else {
    ascii_int -= 65;
  }

  unsigned char lcd_char = charArr[ascii_int];

  //Ausgabe auf LCD
  output(lcd_char, pos, upper_line);
}

void LCD::show_string(const char *text, bool upper_line) {
  int max_chars = upper_line ? 4 : 5;
  bool stop = false;
  //Ausgebe des Strings so weit es geht. Rest wird abgeschnitten
  for (int i = 0; i < max_chars; i++) {
    //Leerzeichenbehandlung
    if (text[i] == 32) {
      output(symbolArr[0], i + 1, upper_line);
    } else if(text[i]==0){
        stop = true;
        output(0b00000000, i+1, upper_line);
    }else if (stop){
        output(0b00000000, i+1, upper_line);
    } else{
      show_char(text[i], i + 1, upper_line);
    }

  }

}
