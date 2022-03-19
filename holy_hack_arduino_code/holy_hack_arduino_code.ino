// libraties toevoegen
#include <Servo.h>
#include <SoftwareSerial.h>
//#include <TimedAction.h>

SoftwareSerial bluetooth(8, 9);
const int redLEDpin = 6;
const int greenLEDpin = 4;
const int blueLEDpin = 5;
const int buzzer_pin = 10;

const char idle = 'a';
const char find_bike = '1';
const char stop_find = '0';
const char buzz_on = '2';
const char buzz_off = '3';

// Define variables
char msg;
bool buzz, searching;
long int t;


void setup() {

  // Bluetooth
  bluetooth.begin(9600);
  delay(100);
  Serial.begin(9600);
  delay(100);

  // Define pins
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);

  // Define variables
  msg = stop_find;
  buzz = true; searching = false;
  t = millis();
}

void loop() {
  // rcv message
  if (bluetooth.available()) {
    msg = bluetooth.read();
    bluetooth.println("Android Command: " + msg);
    Serial.println(msg);
  }

  // Control Arduino board
  switch (msg){
    case find_bike:
      set_color(HIGH, LOW, LOW); // Turn on LED
      if (buzz) tone(buzzer_pin, 1000);
      bluetooth.println("LED is turned on\n"); // Send status message to Android
      searching = true;
      t = millis();
      break;
    case stop_find:
      set_color(LOW, LOW, LOW); // Turn off LED
      noTone(buzzer_pin);
      bluetooth.println("LED is turned off\n"); // Send status message to Android
      searching = false;
      break;
    case buzz_on:
      buzz = true;
      bluetooth.println("Buzzer on");
      break;
    case buzz_off:
      buzz = false;
      bluetooth.println("Buzzer off");
      break;
  }
  msg = idle;

  if (searching) {
    if (millis() - t > 10*1000) {
      set_color(LOW, LOW, LOW);
      searching = false;
    } else if (millis() - t > 5*1000) noTone(buzzer_pin);
  }
  //Serial.println(millis());
  //Serial.println(t);
}

//-------EIGEN FUNCTIES-------

void flikker() {
  for (int i=0; i<3; i++){
    set_color(HIGH, LOW, LOW);
    delay(100);
    set_color(LOW, HIGH, LOW);
    delay(100);
    set_color(LOW, LOW, HIGH);
    delay(100);
  }
  set_color(LOW, LOW, LOW);
}

void set_color(int r, int b, int g) {
  digitalWrite(redLEDpin, r);
  digitalWrite(blueLEDpin, b);
  digitalWrite(greenLEDpin, g);
}
