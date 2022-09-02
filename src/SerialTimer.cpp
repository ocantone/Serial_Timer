#include <Arduino.h>
#include <TimerOne.h>

// This example uses the timer interrupt to blink an LED
// and also demonstrates how to share a variable between
// the interrupt and the main program.


const int led = LED_BUILTIN;  // the pin with a LED
void blinkLED(void);
void setup(void)
{
  pinMode(led, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
// use volatile for shared variables
volatile unsigned long blinkCount = 0; 
unsigned long blinkCopy = 0;  
void blinkLED(void)
{
  if (ledState == LOW) {
    ledState = HIGH;
    blinkCount = blinkCount + 1;  // increase when LED turns on
  } else {
    ledState = LOW;
  }
  digitalWrite(led, ledState);
}

void loop(void)
{
 
  noInterrupts();
if(blinkCopy != blinkCount){
   blinkCopy=blinkCount;

   Serial.print("blinkCount = ");
   Serial.println(blinkCopy);
    }
  interrupts();    
}