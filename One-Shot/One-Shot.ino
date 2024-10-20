constexpr int highTime = 6;  // Time in microseconds for the output to be high

volatile byte eightTimerPreload = 255 - (16 * (highTime - 2));     // Preload value for the timer
volatile int sixteenTimerPreload = 65536 - (16 * (highTime - 2));  // Preload value for the timer

void setup() {
    pinMode(12, OUTPUT);  // outputs 2 ->11, 3 -> 12
    pinMode(11, OUTPUT);

    pinMode(2, INPUT);  // inputs
    pinMode(3, INPUT);

    TCCR1A = 0;  // Set entire TCCR0A register to 0, Init timer0
    TCCR1B = 0;  // Set entire TCCR0B register to 0, Init timer0

    TCCR1B |= 0b00000001;  // Set up timer with no prescaler

    TCNT1 = sixteenTimerPreload;  // Initialize counter value to overflow after 16 cycles, 1us

    TIMSK1 |= 0b00000001;  // Enable timer0 overflow interrupt

    TCCR2A = 0;  // Set entire TCCR2A register to 0, Init timer2
    TCCR2B = 0;  // Set entire TCCR2B register to 0, Init timer2

    TCCR2B |= 0b00000001;  // Set up timer with no prescaler

    TCNT2 = eightTimerPreload;  // Initialize counter value to overflow after 16 cycles, 1us

    TIMSK2 |= 0b00000001;  // Enable timer2 overflow interrupt

    attachInterrupt(digitalPinToInterrupt(2), AInterrupt, RISING);  // Attach interrupt to pin 2
    attachInterrupt(digitalPinToInterrupt(3), BInterrupt, RISING);  // Attach interrupt to pin 3
}

ISR(TIMER1_OVF_vect) {    // Timer0 overflow interrupt, turn off pin as it has been 6us
    PORTB &= 0b11101111;  // Turn off pin 12, leave the rest unchanged
}

ISR(TIMER2_OVF_vect) {    // Timer2 overflow interrupt, turn off pin as it has been 6us
    PORTB &= 0b11110111;  // Turn off pin 11, leave the rest unchanged
}

void AInterrupt() {               // Rising edge interrupt on pin 2
    PORTB |= 0b00010000;          // Turn on pin 12
    TCNT1 = sixteenTimerPreload;  // Reset timer0 to 6us from overflow
}

void BInterrupt() {             // Rising edge interrupt on pin 3
    PORTB |= 0b00001000;        // Turn on pin 11
    TCNT2 = eightTimerPreload;  // Reset timer2 to 6us from overflow
}

void loop() {}
