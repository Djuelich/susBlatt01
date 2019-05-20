/*
 * main.cc - Initialisierung und Threadstart
 *
 * Wenn alle Threads mit Aspekten eingebunden werden, sind
 * in dieser Datei keine Aenderungen notwendig. Wenn nicht,
 * sollten Threadanmeldungen in ready_threads() erfolgen.
 */

#include "device/watch.h"
#include "guard/guard.h"
#include "machine/cpu.h"
#include "machine/system.h"
#include "syscall/guarded_organizer.h"
#include "syscall/thread.h"


// Hier sollten die Includes der eigenen Thread-Headerfiles ergaenzt werden
#include "user/mainthread.h"
#include "user/buttonservice.h"
#include "user/wecker.h"
#include "user/cpuwatch.h"

/* Threads beim Scheduler anmelden */
static void ready_threads() {
  Guarded_Organizer::instance().ready(MainThread::instance());
  Guarded_Organizer::instance().ready(ButtonService::instance());
  Guarded_Organizer::instance().ready(Wecker::instance());
  Guarded_Organizer::instance().ready(CPUWatch::instance());
}

int main() {
  // VCore und Takte konfigurieren
  system_init();

  // Auf Epilogebene wechseln um ungestoert initialisieren zu koennen
  CPU::disable_int();
  Guard::instance().enter();

  // Timerinterrupts einschalten
  Watch::instance().windup();
  CPU::enable_int();

  // Threads aktivieren
  ready_threads();

  // Scheduling starten
  Guarded_Organizer::instance().Organizer::schedule();

  // Endlosschleife - wird nie erreicht, spart aber ein wenig Speicher
  while (1) ;
}
