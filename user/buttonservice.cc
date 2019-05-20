#include "user/buttonservice.h"

#include "machine/system.h"
#include "machine/buttons.h"
#include "syscall/guarded_semaphore.h"

Guarded_Semaphore button_semaphore(1);
Guarded_Semaphore lcd_semaphore(1);


void ButtonService::action () {
	while (1) {
		/* Watchdog zuruecksetzen */
		//watchdog_reset();

		// Fragt Button Zustand ab
		button_state = Buttons::instance().read();

		//Typische Prellzeiten bei elektromechanischen Schaltern und Tastern liegen im Zeitbereich 100 µs bis 10 ms. (wikipedia)
		//Für 20ms schlafen legen um sicher zu gehen
		mybuzz.set(20);
		mybuzz.sleep();

		//Testen ob Zustand richtig war oder nur ein Prellen und nur bei erfolgreichem Test freigeben.
		if(Buttons::instance().pressed(button_state)){
			button_semaphore.signal();
			/*if(Buttons::instance().pressed(Buttons::HASH)){
				lcd_semaphore.signal();
			}*/
		}

		//Schlafen legen bis zum nächsten Test
		mybuzz.set(80);
		mybuzz.sleep();

	}
}


uint8_t ButtonService::wait_for_buttons(){
	//Semaphore locken bis es sicher ist die Buttons abzufragen
	button_semaphore.wait();
	return button_state;
}

void ButtonService::wait_for_lcd(){
	lcd_semaphore.wait();
}

void ButtonService::signal_for_lcd(){
	//button_semaphore.wait();
	//Buttons::instance().pressed(button_state & Buttons::HASH);
	lcd_semaphore.signal();
}
