#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define ESC1_PIN 3
#define ESC2_PIN 5
#define ESC3_PIN 9
#define ESC4_PIN 11

int incomingByte = 0;

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  ESC1.attach(ESC1_PIN);
  ESC2.attach(ESC2_PIN);
  ESC3.attach(ESC3_PIN);
  ESC4.attach(ESC4_PIN);

  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  ESC1.writeMicroseconds(MAX_SIGNAL);
  ESC2.writeMicroseconds(MAX_SIGNAL);
  ESC3.writeMicroseconds(MAX_SIGNAL);
  ESC4.writeMicroseconds(MAX_SIGNAL);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  ESC1.writeMicroseconds(MIN_SIGNAL);
  ESC2.writeMicroseconds(MIN_SIGNAL);
  ESC3.writeMicroseconds(MIN_SIGNAL);
  ESC4.writeMicroseconds(MIN_SIGNAL);
  
  Serial.println("Calibration complete");
}

void loop() {  
  /*
  ESC1.writeMicroseconds(800);
  ESC2.writeMicroseconds(800);
  ESC3.writeMicroseconds(800);
  ESC4.writeMicroseconds(800);
*/
  int increment = (1000-MIN_SIGNAL)/10; //increments of 10
  
  for(int fadeValue = MIN_SIGNAL; fadeValue <= 1000; fadeValue += increment){
    ESC1.writeMicroseconds(fadeValue);
    ESC2.writeMicroseconds(fadeValue);
    ESC3.writeMicroseconds(fadeValue);
    ESC4.writeMicroseconds(fadeValue);
    delay(5000);
    Serial.println(fadeValue);
    }
    
   if (Serial.available() >= '0')
   {
     incomingByte = Serial.read();
     Serial.println(incomingByte);

     if (incomingByte=='0') { 
     while(1); 
     }
   }
}
