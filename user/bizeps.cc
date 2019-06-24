#include "user/bizeps.h"

#include "machine/system.h"
#include "machine/lcd.h"
#include "user/buttonservice.h"
#include "machine/buttons.h"
#include "machine/beeper.h"
#include "syscall/guarded_accel.h"
#include "syscall/guarded_radio.h"
#include "machine/simpliciti/radioconfig.h"
#include "machine/timer.h"


Bizeps::Bizeps_state Bizeps::current_state = Init;
void Bizeps::action () {

	ButtonService::instance().wait_for_lcd();

	Guarded_Accel &accel = Guarded_Accel::instance();
	accel.set_mode(Accel::Mode::MEASURE_100HZ, Accel::Range::RANGE_2G);
	Beeper::instance().init();
	int game_over_screen_time = 10000;

	int time = 0;

	while (1) {


		/* Watchdog zuruecksetzen */
		//watchdog_reset();


		switch(current_state){
			case Init:
				LCD::instance().show_string("Bizep", false);
				LCD::instance().show_string("", true);

				ButtonService::instance().wait_for_buttons();
				if(Buttons::instance().pressed( Buttons::HASH)){
					ButtonService::instance().signal_for_lcd(); // v()
					mybuzz.set(10); //  Anderen  Threads  Zeit  geben , das  Mutex zu  bekommen
					mybuzz.sleep();
					ButtonService::instance().wait_for_lcd(); // p()
				}



				if(Buttons::instance().pressed( Buttons::STAR)){
					Guarded_Radio::instance().enable_rx();
					unsigned char send_msg[] = {'b', 0}; //0 für init und b für die bizeps funktion
					Guarded_Radio::instance().send_broadcast(send_msg, 2);
					current_state = Ready;

				}

				break;


			case Ready:
				LCD::instance().show_string("Ready", false);
				unsigned char data[MAX_APP_PAYLOAD];
				unsigned char lengthptr;

				if (Guarded_Radio::instance().receive_broadcast(data, &lengthptr)){
					if ( data[0] == 'b'){
						if(data[1] == 0){
							unsigned char send_msg[] = {'b', 1}; //1 für ready und b für die bizeps funktion
							Guarded_Radio::instance().send_broadcast(send_msg, 2);

						}

						Guarded_Radio::instance().disable_rx();
						current_state = Countdown;

					}
				}
				break;

			case Countdown:
				LCD::instance().show_string("Count", false);
				for (int i = 3; i > 0; i--){
					LCD::instance().show_number(i, true);
					Beeper::instance().beep(3000, 500);
					mybuzz.set(1000);
					mybuzz.sleep();
				}
				Beeper::instance().beep(5000, 1000);

				current_state = Game;
				break;

			case Game:

				LCD::instance().show_string("Fight", false);
				Timer::stop();
				time += Timer::getcycles();
				if (time > 30000){
					current_state = Tie;
				}
				LCD::instance().show_number(30 - (time /1000), true);

				Timer::start();
				if (accel.data_available()) {
					signed char y = accel.read_y();
					signed char z = accel.read_z();
					LCD::instance().show_string("", false);


					if(y < 5){
						if(z < 0){
							//win
							Beeper::instance().beep(2400, 1000);
		                	Beeper::instance().beep(4400, 1000);
		                	current_state = Win;
						} else if (z > 0){
							//lose
							Beeper::instance().beep(440, 1000);
							Beeper::instance().beep(240, 1000);
							current_state = Lose;
						}
					}
				}

				break;

			case Win:

				LCD::instance().show_string("fata", true);
				LCD::instance().show_string("lity", false);
				accel.set_mode(Accel::Mode::POWERDOWN, Accel::Range::RANGE_2G);
				mybuzz.set(game_over_screen_time);
				mybuzz.sleep();
				current_state = Init;

				break;


			case Lose:

				LCD::instance().show_string("noob", true);
				LCD::instance().show_string("lauch", false);
				accel.set_mode(Accel::Mode::POWERDOWN, Accel::Range::RANGE_2G);
				mybuzz.set(game_over_screen_time);
				mybuzz.sleep();
				current_state = Init;

				break;


			case Tie:

				LCD::instance().show_string("Lame", true);
				LCD::instance().show_string("Fight", false);
				accel.set_mode(Accel::Mode::POWERDOWN, Accel::Range::RANGE_2G);
				mybuzz.set(game_over_screen_time);
				mybuzz.sleep();
				current_state = Init;

				break;


		}







	}
}
