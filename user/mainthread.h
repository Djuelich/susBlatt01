#ifndef USERTHREAD_H
#define USERTHREAD_H

#include "syscall/thread.h"
#include "syscall/guarded_buzzer.h"

class MainThread : public UserThread<512> { // 512 Byte Stack
private:
  Guarded_Buzzer buzzer;

public:
  /* Die Methode action() ist der Einstiegspunkt des Threads */
  void action();

  /* Methode zum Zugriff auf die Singleton Instanz */
  static MainThread& instance() {
    static MainThread mainthread; // Singleton Instanz
    return mainthread;
  }

  // Diesen Thread fuer "ms" Millisekunden schlafen legen,
  // um Strom zu sparen.
  void sleep(unsigned int ms) {
    buzzer.set(ms);
    buzzer.sleep();
  }
};

#endif

