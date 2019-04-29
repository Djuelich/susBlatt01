/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

#ifndef __organizer_include__
#define __organizer_include__

#include "thread/customer.h"
#include "thread/scheduler.h"
#include "meeting/waitingroom.h"

class Organizer : public Scheduler {
private:
  Organizer(const Organizer &copy); // Verhindere Kopieren

protected:
  Organizer() {}

public:
  void block(Customer &customer, Waitingroom &waitingroom);
  void wakeup(Customer &customer);
  void kill(Customer &that);
};

#endif
