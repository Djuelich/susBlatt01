# ifndef BUTTONSERVICE_H
# define BUTTONSERVICE_H

# include "syscall/thread.h"
# include "syscall/guarded_buzzer.h"

class ButtonService : public UserThread <512> {
	Guarded_Buzzer mybuzz;

public :
	ButtonService(): UserThread(){}

	void action ();

	void wait_for_buttons();
	
	// Methode zum Zugriff auf die Singleton - Instanz
	static ButtonService & instance () {
		static ButtonService buttonService ;
		return buttonService ;
	}
};
# endif /* BUTTONSERVICE_H */