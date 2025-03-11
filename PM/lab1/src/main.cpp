#include <util/delay.h>
#include <usart.c>

#define CLOCK_SPEED 12000000
#define BAUD 9600
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

int main() {

    USART0_init(MYUBRR);

    // Button 1 load
    DDRB &= ~(1 << PB2);
    PORTB &= (1 << PB2);

    // Red
    DDRD |= (1 << PD5);
    PORTD |= (1 << PD5);

    // Green
    DDRD |= (1 << PD7);
    PORTD |= (1 << PD7);

    // Blue
    DDRB |= (1 << PB3);
    PORTB |= (1 << PB3);


    while (true) {
        // Button 1 test
        // if (!(PINB & (1 << PB2))) {
        //     USART0_print("Button 1 pressed\n");
        //     _delay_ms(500);
        // }

        // check command
        char cmd[10];
        int i = 0;
        
        while (i < 10) {
            char chr = USART0_receive();
            if (chr == '\n') {
                break;
            }
            cmd[i++] = chr;
        }
        cmd[i] = '\0';
        USART_exec(cmd);

        // morse
        // char *txt = "ubuntu";
        // for (int i = 0; i < 6; i ++) {

        // }
    }

	return 0;
}