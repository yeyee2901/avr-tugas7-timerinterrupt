#include <avr/io.h>
#include <avr/interrupt.h>

// MACROS ---------------------------
#define F_CPU 5000000UL

// DEBUG ----------------------------
#include <simulavr_info.h>
SIMINFO_DEVICE("atmega8");
SIMINFO_CPUFREQUENCY(5000000);

// VARIABLE DEFINITION
uint8_t compA_flag = 0;
uint8_t compB_flag = 0;
uint8_t compA_count = 0;
uint8_t count_limit = 10;

// MAIN PROGRAM ---------------------
void setup(){

    // Setup Timer1 as compare match event
    // prescaler 8 (tick = 1.6 us)
    // timer1 set in CTC mode (WGM12 @TCCR1B) 
    // interrupts: compare match A & B (OCIE1A & OCIE1B @TIMSK)
    //
    // Compare match A to toggle PD0 every 30ms
    // Compare match B to toggle PD1 15ms BEFORE every compare match A occurs 
    //  resulting in 90 phase shifted waveform in PD1
    // every 10 compare match A, toggle PD2 & PD3 (ideally every 300 ms)
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    TIMSK  |= (1 << OCIE1B) | (1 << OCIE1A);
    OCR1A  = 18750;
    OCR1B  =  9375;

    // setup PORTD as outputs
    DDRD  = 0x0F;
    PORTD = 0;
}

void main(void){

    setup();

    // enable global interrupt bit
    sei();

    while(1){

        if(compA_flag){
            PORTD ^= (1 << PD0);
            compA_flag = 0;
            compA_count++;
        }

        if(compB_flag){
            PORTD ^= (1 << PD1);
            compB_flag = 0;
        }

        // if compare match A occurs 10x (ideally 300ms),
        // toggle PD2 & PD3, then reset compare match B count
        if(compA_count >= count_limit){
            PORTD ^= ((1 << PD2) | (1 << PD3));
            compA_count = 0;
        }
    }
}

// INTERRUPT ROUTINE ---------------
// compare match A every 30ms
ISR(TIMER1_COMPA_vect){
    compA_flag = 1;
}

// compare match B every 1ms
ISR(TIMER1_COMPB_vect){
    compB_flag = 1;
}
