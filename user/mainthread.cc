#include "user/mainthread.h"
#include <msp430.h>
#include "machine/system.h"
#include "machine/lcd.h"

void MainThread::action() {
  while (1) {
    /* Fuer 100ms schlafen legen, um Strom zu sparen */
    this->sleep(100);

    /* Watchdog anstossen */
    watchdog_reset();
    // Hier muesst ihr selbst Code ergaenzen
    
    //show_number testsection
    //LCD::instance().show_number(number,true/false);

    //show_digit testsection
    //TODO Fehlerbehandlung für mehrere pos = n
    
    /*LCD::instance().show_digit(0, 1, true); // Beispielsweiser LCD-Zugriff
    LCD::instance().show_digit(1, 2, true);
    LCD::instance().show_digit(2, 3, true);
    LCD::instance().show_digit(3, 4, true);

    LCD::instance().show_digit(4, 1, false);
    LCD::instance().show_digit(5, 2, false);
    LCD::instance().show_digit(6, 3, false);
    LCD::instance().show_digit(7, 4, false);
    LCD::instance().show_digit(8, 5, false);
  }
  */
    //show_char testsection
    LCD::instance().show_char(1,1, false);

    //show_string testsection
    /*
    LCD::instance().show_string(text, true/false)
    */

  // Achtung: Die action()-Methode darf nicht zurueckkehren,
  //          daher die Endlosschleife!
}