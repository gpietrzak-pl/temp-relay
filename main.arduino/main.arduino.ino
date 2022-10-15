#include "DHT.h"
#include <TM1637Display.h> //https://github.com/avishorp/TM1637

#define DHT11_PIN 2
#define CLK 4
#define DIO 5

//Create objects
DHT dht; 
TM1637Display display = TM1637Display(CLK, DIO);

// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

// constant pins
const int buttonPin = 10; // the number of the pushbutton pin
const int    ledPin = 13; // the number of the LED pin
const int  relayPin =  7; // the number of the relay pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int temperatura = 0;
int wilgotnosc = 0;
int zadanaTemperatura = 20;

// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// Create degree Celsius symbol:
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

void SetRelay(int temperature, int setTemperature)
{
  if (temperature > setTemperature) {
   digitalWrite(relayPin, HIGH); 
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
}

void setup()
{
  // initialize an output pins:
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // initialize an input pins:
  pinMode(buttonPin, INPUT);  
  
  // initial config
  dht.setup(DHT11_PIN);
  display.clear();
  display.setBrightness(1);
}
 
void loop()
{
 // read the state of the pushbutton value:
  buttonState = !digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    if(zadanaTemperatura <= 50){
        zadanaTemperatura = zadanaTemperatura + 5;
    display.showNumberDec(zadanaTemperatura, false, 2, 0);
    }
    else{
      zadanaTemperatura = 20;
      display.showNumberDec(zadanaTemperatura, false, 2, 0);
    }
    delay(1000);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  SetRelay(dht.getTemperature(),zadanaTemperatura);
  
  display.showNumberDec(dht.getTemperature(), false, 2, 0);
  display.setSegments(celsius, 2, 2);
}
