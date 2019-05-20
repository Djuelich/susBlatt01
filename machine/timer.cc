#include "config.h"
#include <msp430.h>
#include "device/plugbox.h"
#include "machine/timer.h"

Timer::Timer(unsigned long us) {
  ticktime = 1000000L/us;
}

void Timer::plugin() {
  /* Interrupthandler anmelden */
  // FIXME: Umstellen auf CC0 statt Misc!
  Plugbox::instance().assign(Plugbox::Timer0_Misc, *this);

  /** Timer 0: Systemtimer **/
#if 1
  // Stromsparende Variante
  /* Kein weiterer Teiler */
  TA0EX0 = 0;

  /* Maximalen Zaehlerwert einstellen */
  TA0CCR0 = (32878 / ticktime) - 1;

  /* Timer 0 zaehlt ACLK aufwaerts */
  TA0CTL = TASSEL__ACLK | ID_0 | MC__UP;
#endif

#if 0
  // Exakte Variante
  /* Timer 0 zaehlt SMCLK/8 aufwaerts */
  /* Weiteren /4-Teiler einfuegen */
  TA0EX0 = (4-1);

  /* Maximalen Zaehlerwert einstellen */
  TA0CCR0 = (CONFIG_CPU_FREQUENCY / 8 / 4 / ticktime) - 1;

  /* Timer 0 zaehlt SMCLK/8 aufwaerts */
  TA0CTL = TASSEL__SMCLK | ID_3 | MC__UP;
#endif

  /* Timer-Interrupts zulassen */
  TA0CTL |= TAIE;
}

bool Timer::prologue() {
  if (TA0IV == 0x0e) {
    /* Timer overflow */
    return true;
  } else
    /* Andere Timer-Interrupts ignorieren */
    return false;
}

void Timer::delay_us(unsigned int us) {
  /* Grob, aber ausreichend */
  for (unsigned int i=0; i<us/5; i++)
    asm volatile ("nop");
}


/** Mikrosekunden-Zaehler **/
static unsigned int counter;

void Timer::start() {
  counter = TA0R;
}

void Timer::stop() {
  unsigned int now = TA0R;
  if(now >= counter) {
    counter = now - counter; // einfache Differenz
  }
  else {
    counter = (TA0CCR0 - counter) + now; // Ueberlaufbehandlung
  }
}

unsigned int Timer::getcycles() { return counter; }

