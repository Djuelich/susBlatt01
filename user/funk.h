# ifndef FUNK_H
# define FUNK_H

# include "syscall/thread.h"
# include "syscall/guarded_buzzer.h"

class Funk : public UserThread <512> {
	Guarded_Buzzer mybuzz;
	static unsigned char channel;

	enum Funk_state {
		Config,
		Radio
		
	};

	static Funk_state current_state;


public :

	
	void action ();
	
	// Methode zum Zugriff auf die Singleton - Instanz
	static Funk & instance () {
		static Funk funk;
		return funk;
	}
};
# endif /* FUNK_H */