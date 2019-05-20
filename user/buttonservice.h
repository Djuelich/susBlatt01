# ifndef BUTTONSERVICE_H
# define BUTTONSERVICE_H

#include "syscall/thread.h"
#include "syscall/guarded_buzzer.h"

#include "machine/system.h"
#include "machine/buttons.h"
#include "syscall/guarded_semaphore.h"


class ButtonService : public UserThread <512> {
	Guarded_Buzzer mybuzz;
	uint8_t button_state;

public :
	ButtonService(): UserThread(){}

	void action ();

	uint8_t wait_for_buttons();
	void wait_for_lcd();
	void signal_for_lcd();

	// Methode zum Zugriff auf die Singleton - Instanz
	static ButtonService & instance () {
		static ButtonService buttonService ;
		return buttonService ;
	}
};
# endif /* BUTTONSERVICE_H */
