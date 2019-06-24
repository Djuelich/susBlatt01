# ifndef BIZEPS_H
# define BIZEPS_H

# include "syscall/thread.h"
# include "syscall/guarded_buzzer.h"

class Bizeps : public UserThread <512> {
	Guarded_Buzzer mybuzz;

    enum Bizeps_state {
        Init,
        Ready,
        Countdown,
        Game,
        Win,
        Lose,
        Tie
    };

    static Bizeps_state current_state;




public :


	void action ();

	// Methode zum Zugriff auf die Singleton - Instanz
	static Bizeps & instance () {
		static Bizeps bizeps ;
		return bizeps ;
	}
};
# endif /* BIZEPS_H */
