#include "user/funk.h"

#include "machine/system.h"
#include "machine/lcd.h"
#include "user/buttonservice.h"
#include "machine/buttons.h"
#include "machine/beeper.h"
#include "syscall/guarded_radio.h"
#include "machine/simpliciti/radioconfig.h"

//Werte initialisieren
Funk::Funk_state Funk::current_state = Config;
unsigned char Funk::channel = 0;

void Funk::action () {

	unsigned char msg[] = {2,2,2,2,2};
	int length =2;

	ButtonService::instance().wait_for_lcd();
	while (1) {


		/* Watchdog zuruecksetzen */
		//watchdog_reset();

		//Zeigt channel in der oberen Reihe an



		//ZUstandsmaschine
		switch(current_state){

			case Config:
				LCD::instance().show_string("sms", true);
				LCD::instance().show_number(channel, false);
				//Warten auf ButtonService zum Entprellen
				ButtonService::instance().wait_for_buttons();
				if(Buttons::instance().pressed( Buttons::HASH)){
					ButtonService::instance().signal_for_lcd(); // v()
					mybuzz.set(10); //  Anderen  Threads  Zeit  geben , das  Mutex zu  bekommen
					mybuzz.sleep();
					ButtonService::instance().wait_for_lcd(); // p()
				}

				if(Buttons::instance().pressed( Buttons::STAR)){
					current_state = Radio;
					break;
				} else if (Buttons::instance().pressed(Buttons::UP)) {
					//Falls über 100,00s dann fängt man bei 0 an
					if((channel + 1)  > 9){
						channel = 0;
					} else {
						channel++; //1s inkrementiren
					}

				} else if (Buttons::instance().pressed(Buttons::DOWN)) {
					//falls unter 0s fängt man bei 100,00s an
					if((channel - 1) < 0){
						channel = 9;
					} else {
						channel--; //1s dekrementieren
					}
				}
				break;

			case Radio:
				LCD::instance().show_char('c', 1, true);
				LCD::instance().show_char('h', 2, true);
				LCD::output(0b00000000, 3, true);
				LCD::instance().show_digit(channel, 4, true);

				Guarded_Radio::instance().enable_rx();

				ButtonService::instance().wait_for_buttons();
				if(Buttons::instance().pressed( Buttons::STAR)){
					current_state = Config;
					Guarded_Radio::instance().disable_rx();
					break;
				}

				unsigned char data[MAX_APP_PAYLOAD];
				unsigned char lengthptr;

				if (Guarded_Radio::instance().receive_broadcast(data, &lengthptr)){
					//LCD::instance().show_string("happy", false);
					if(lengthptr == 2){
						if(channel == data[0]){
							msg[4] = msg[3];
							msg[3] = msg[2];
							msg[2] = msg[1];
							msg[1] = msg[0];
							msg[0] = data[1];
						}

					}


				}

				for(int i = 0; i < 5; i++){
					if(msg[i] == 0){
						LCD::instance().output(0b00000010, i+1, false);
					} else if( msg[i] == 1){
						LCD::instance().show_digit(0, i+1, false);
					} else {
						LCD::instance().output(0b00000000, i+1, false);
					}

				}

				ButtonService::instance().wait_for_buttons();
				if (Buttons::instance().pressed(Buttons::UP)) {
					unsigned char send_msg[] = {channel, 1};
					Guarded_Radio::instance().send_broadcast(send_msg, length);
				} else if (Buttons::instance().pressed(Buttons::DOWN)) {
					unsigned char send_msg[] = {channel, 0};
					Guarded_Radio::instance().send_broadcast(send_msg, length);
				}


				break;


		}

	}
}
