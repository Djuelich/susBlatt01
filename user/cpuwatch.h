# ifndef CPUWATCH_H
# define CPUWATCH_H

# include "syscall/thread.h"
# include "syscall/guarded_buzzer.h"

class CPUWatch : public UserThread <512> {
	Guarded_Buzzer mybuzz;
	static int time;


public :


	void action ();
    void dummy();

	// Methode zum Zugriff auf die Singleton - Instanz
	static CPUWatch & instance () {
		static CPUWatch cpuw ;
		return cpuw ;
	}
};
# endif /* CPUWATCH_H */
