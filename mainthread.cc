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
    LCD::instance().show_digit(8, 1, true); // Beispielsweiser LCD-Zugriff
    LCD::instance().show_digit(9, 2, true);
    LCD::instance().show_digit(0, 3, true);
    LCD::instance().show_digit(7, 4, true);

    LCD::instance().show_digit(5, 1, false);
    LCD::instance().show_digit(6, 2, false);
    LCD::instance().show_digit(7, 3, false);
    LCD::instance().show_digit(8, 4, false);
    LCD::instance().show_digit(9, 5, false);
  }
  // Achtung: Die action()-Methode darf nicht zurueckkehren,
  //          daher die Endlosschleife!
}
