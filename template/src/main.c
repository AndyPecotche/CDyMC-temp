#include <avr/io.h> // Definici�n de Registros del microcontrolador
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software � Macros: depende de F_CPU
const unsigned int DELAY = 80;//ms
#include <stdio.h>
#include <avr/interrupt.h>

int main(void)
{
	_delay_ms(1000);
	
	// Configurar LED integrado (D13, PB5) como salida
	DDRB |= (1<<PB5);
	// Configurar D2 (PD2) como entrada con pull-up interna
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);

 	while (1) 
    {
		// Leer PD2 (D2) con pull-up interna: si se conecta a GND -> LOW -> encender LED
		if (!(PIND & (1<<PD2))) {
			PORTB |= (1<<PB5); // encender LED integrado
		} else {
			PORTB &= ~(1<<PB5); // apagar LED
		}
		
    }
}
