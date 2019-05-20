#include "user/wecker.h"

#include "machine/system.h"
#include "machine/lcd.h"
#include "user/buttonservice.h"
#include "machine/buttons.h"
#include "machine/beeper.h"

//Werte initialisieren
Wecker::Wecker_state Wecker::current_state = Config;
int Wecker::time = 0;

void Wecker::action () {

	ButtonService::instance().wait_for_lcd();
	while (1) {


		/* Watchdog zuruecksetzen */
		//watchdog_reset();

		//Zeigt TIME in der oberen Reihe an
		LCD::instance().show_string("time", true);


		//ZUstandsmaschine
		switch(current_state){

			case Config:
				LCD::instance().show_number(time, false);
				//Warten auf ButtonService zum Entprellen
				ButtonService::instance().wait_for_buttons();
				if(Buttons::instance().pressed( Buttons::HASH)){
					ButtonService::instance().signal_for_lcd(); // v()
					mybuzz.set(10); //  Anderen  Threads  Zeit  geben , das  Mutex zu  bekommen
					mybuzz.sleep();
					ButtonService::instance().wait_for_lcd(); // p()
				}
				if(Buttons::instance().pressed( Buttons::STAR)){
					current_state = Countdown;
					break;
				} else if (Buttons::instance().pressed(Buttons::UP)) {
					//Falls über 100,00s dann fängt man bei 0 an
					if((time + 100)  > 10000){
						time -= 10000;
					} else {
						time += 100; //1s inkrementiren
					}

				} else if (Buttons::instance().pressed(Buttons::DOWN)) {
					//falls unter 0s fängt man bei 100,00s an
					if((time - 100) < 0){
						time += 10000;
					} else {
						time -= 100; //1s dekrementieren
					}
				}
				break;

			case Countdown:
				LCD::instance().show_number(time, false);

				//Falls Zeit um Alarm
				if(time == 0){
					current_state = Alarm;
					break;
				}

				//Zeit runterzählen
				time--;

				mybuzz.set(10);
				mybuzz.sleep();

				//timer anhalten
				ButtonService::instance().wait_for_buttons();
				if(Buttons::instance().pressed(Buttons::STAR)){
					current_state = Config;
				}
				break;

			case Alarm:
				//Alarm ausgeben
				LCD::instance().show_string("Alarm", false);
				//Alarmton ausgeben
				Beeper::instance().init();
                Beeper::instance().beep(4400, 3000);
				//Nach Alarmton wieder in Config Zusatand gehen
				mybuzz.set(3000);
				mybuzz.sleep();
				current_state = Config;
				break;
		}

	}
}
