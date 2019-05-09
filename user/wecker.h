# ifndef WECKER_H
# define WECKER_H

# include "syscall/thread.h"
# include "syscall/guarded_buzzer.h"

class Wecker : public UserThread <512> {
	Guarded_Buzzer mybuzz;
	static int time;

	enum Wecker_state {
		Config,
		Countdown,
		Alarm
	};

	static Wecker_state current_state;


public :

	
	void action ();
	
	// Methode zum Zugriff auf die Singleton - Instanz
	static Wecker & instance () {
		static Wecker wecker ;
		return wecker ;
	}
};
# endif /* WECKER_H */