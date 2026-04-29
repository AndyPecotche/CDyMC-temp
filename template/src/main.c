//#define F_CPU 16000000UL
#include <avr/io.h> // Definicion de Registros del microcontrolador
#include <avr/interrupt.h>
#include <util/delay.h> 
//#include <vcd.h> // Para usar la funcionalidad de VCD (con simavr)
#include "avr8-stub.h" // Para usar la funcionalidad de GDB stub (con avr-stub)

int main(void)
{
	int LED = 0;
	int contador = 0;
  	
	debug_init(); // inicializar GDB stub
	sei(); //AVR-STUB usa interrupciones para gestionar breakpoints y pasos desde el IDE, por lo que es necesario habilitar las interrupciones globales con sei().

	// Configurar LED integrado (D13, PB5) como salida
	DDRB |= (1<<PB5);
	// Configurar D3 (PD3) como entrada con pull-up interna
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);
 	while (1) {
	// 	// Leer PD3, si se conecta a GND -> LOW -> encender LED (marcar FLAG encendido)
	 	if (!(PIND & (1<<PD2))) {
			LED = 1;
	 	} else {
			LED = 0;
	 	}

		if (LED) {
			PORTB |= (1<<PB5); // encender LED
		}else {
			PORTB &= ~(1<<PB5); // apagar LED
		}
		contador++;
	}
}
