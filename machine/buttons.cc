#include "buttons.h"
#include <msp430.h> // definiert Acronyme (Digital I/O Registers)

Buttons Buttons::buttons; // // Singleton Instanz

// Hier muesst ihr selbst Code ergaenzen
void Buttons::enable(uint8_t button_bitmap){
	//die in button_bitmap spezifizierten I/O Pins der entsprechenden Buttons konfigurieren
	P2OUT = P2OUT & ~button_bitmap;
	P2DIR = P2DIR & ~button_bitmap;
	P2REN = P2REN | button_bitmap;
}


uint8_t Buttons::read(){
	//Status der Input-Pins so maskieren, dass nur die Zustände der 4 konfigurierbaren buttons ausgegeben werden
	return P2IN & 0b00010111;
}

bool Buttons::pressed(uint8_t button_bitmap){
	//Testen ob die von button_bitmap spezifizierten buttons gedrückt sind
	return (read() == button_bitmap);
}
