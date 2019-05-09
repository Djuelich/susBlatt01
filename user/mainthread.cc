#include "user/mainthread.h"
#include <msp430.h>
#include "machine/system.h"
#include "machine/lcd.h"
#include "machine/buttons.h"

void MainThread::action() {
  while (1) {
    /* Fuer 100ms schlafen legen, um Strom zu sparen */
    this->sleep(100);

    /* Watchdog anstossen */
    watchdog_reset();

    //Testsektion. Auskommentieren zum testen.
    Buttons::instance().enable(Buttons::UP | Buttons::DOWN | Buttons::STAR);


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

    /*
    if (Buttons::instance().pressed(Buttons::UP))
    {
      LCD::instance().show_digit(1, 1, true);
    }else{
      LCD::instance().show_digit(0, 1, true);
    }
    
    if (Buttons::instance().pressed(Buttons::DOWN))
    {
      LCD::instance().show_digit(1, 2, true);
    }else{
      LCD::instance().show_digit(0, 2, true);
    }

    if (Buttons::instance().pressed(Buttons::STAR))
    {
      LCD::instance().show_digit(1, 3, true);
    }else{
      LCD::instance().show_digit(0, 3, true);
    }

    if (Buttons::instance().pressed(Buttons::HASH))
    {
      LCD::instance().show_digit(1, 4, true);
    }else{
      LCD::instance().show_digit(0, 4, true);
    }
    */
    
    //LCD::instance().show_number(Buttons::instance().read(), true);

    /*
      LCD::instance().show_char('A', 1, true);
      LCD::instance().show_char('a', 2, true);
      LCD::instance().show_char('B', 3, true);
      LCD::instance().show_char('b', 4, true);

      LCD::instance().show_char('C', 1, false);
      LCD::instance().show_char('c', 2, false);
      LCD::instance().show_char('D', 3, false);
      LCD::instance().show_char('d', 4, false);
      LCD::instance().show_char('k', 5, false);
    */

    /*
      LCD::instance().show_string("Hi", true);
      LCD::instance().show_string("Welt", false);
    */
  }
  // Achtung: Die action()-Methode darf nicht zurueckkehren,
  //          daher die Endlosschleife!
}