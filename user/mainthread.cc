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

    /*
    LCD::instance().show_digit(1, 1, true); // Beispielsweiser LCD-Zugriff
    LCD::instance().show_digit(2, 2, true);
    LCD::instance().show_digit(3, 3, true);
    LCD::instance().show_digit(4, 4, true);

    LCD::instance().show_digit(5, 1, false);
    LCD::instance().show_digit(6, 2, false);
    LCD::instance().show_digit(7, 3, false);
    LCD::instance().show_digit(8, 4, false);
    LCD::instance().show_digit(9, 5, false);
  */
    //LCD::instance().show_number(333, true);

    LCD::instance().show_char('A', 1, true);
    LCD::instance().show_char('a', 2, true);
    LCD::instance().show_char('B', 3, true);
    LCD::instance().show_char('b', 4, true);

    LCD::instance().show_char('C', 1, false);
    LCD::instance().show_char('c', 2, false);
    LCD::instance().show_char('D', 3, false);
    LCD::instance().show_char('d', 4, false);
    LCD::instance().show_char('E', 5, false);

    //LCD::instance()show_string(text, true/false);

  }
  // Achtung: Die action()-Methode darf nicht zurueckkehren,
  //          daher die Endlosschleife!
}