#include "user/cpuwatch.h"

#include "machine/system.h"
#include "machine/lcd.h"
#include "user/buttonservice.h"
#include "machine/buttons.h"
#include "machine/beeper.h"
#include "machine/timer.h"
#include "user/idletimer.ah"

//Werte initialisieren
/*int IdleTimer::idleTime = 0;
int IdleTimer::totalTime = 0;
bool IdleTimer::idle = false;
*/


void CPUWatch::action () {

    ButtonService::instance().wait_for_lcd();
	while (1) {


		/* Watchdog zuruecksetzen */
		//watchdog_reset();

        //Zeigt idle in der oberen Reihe an
        LCD::instance().show_string("idle", true);

        //hook für Ausgabe advice
        dummy();

        ButtonService::instance().wait_for_buttons();
        if(Buttons::instance().pressed( Buttons::HASH)){
            ButtonService::instance().signal_for_lcd(); // v()
            mybuzz.set(10); //  Anderen  Threads  Zeit  geben , das  Mutex zu  bekommen
            mybuzz.sleep();
            ButtonService::instance().wait_for_lcd(); // p()
        }
	}
}

void CPUWatch::dummy(){}
