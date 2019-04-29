/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        G U A R D E D _ A C C E L                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Schnittstelle von Anwendungsthreads zum Accel-Objekt                      */
/*****************************************************************************/

#include "syscall/guarded_accel.h"
#include "guard/secure.h"

Guarded_Accel::Guarded_Accel() {
  plugin();
}

void Guarded_Accel::set_mode(Mode::mode_t mode, Range::range_t range) {
  Secure sec;

  Accel::set_mode(mode, range);
}

signed char Guarded_Accel::read_register(Register::register_t reg) {
  Secure sec;

  return Accel::read_register(reg);
}
