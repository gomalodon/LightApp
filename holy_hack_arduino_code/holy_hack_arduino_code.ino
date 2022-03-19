// libraties toevoegen
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(8, 9);
const int redLEDpin = 6;
const int greenLEDpin = 4;
const int blueLEDpin = 5;
const int buzzer_pin = 10;

// definitie variabelen
String message;

void setup() {

  // Monitor and bluetooth
  bluetooth.begin(9600);
  delay(100);
  Serial.begin(9600);
  delay(100);

  // Define pins
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);

  // Test connection
  Serial.println("test");

  // set varialbles
  message = "";
}

void loop() {
  // rcv message
  if (bluetooth.available()) {
    message = bluetooth.readString();
    bluetooth.println("Android Command: " + message);
  }

  // Control LED on Arduino board
  if (message == "<turn on>"){
    set_color(HIGH, HIGH, HIGH); // Turn on LED
    tone(buzzer_pin, 1000);
    bluetooth.println("LED is turned on\n"); // Send status message to Android
    message = ""; // reset command
  } else {
    if (message == "<turn off>"){
      set_color(LOW, LOW, LOW); // Turn off LED
      noTone(buzzer_pin);
      bluetooth.println("LED is turned off\n"); // Send status message to Android
      message = ""; // reset command
    }
  }
}

//-------EIGEN FUNCTIES-------

void wait_for(String message){
  bool klaar = true;
  while (klaar){                 // wachten tot 'OK' wordt ontvangen
    if (Serial.available()) {
      String read = Serial.readString();
      if (read == message+"\n") {
        klaar = false;
      }
    }
  }
}

void flikker() {
  for (int i=0; i<3; i++){
    set_color(HIGH, LOW, LOW);
    delay(500);
    set_color(LOW, HIGH, LOW);
    delay(500);
    set_color(LOW, LOW, HIGH);
    delay(500);
  }
  set_color(LOW, LOW, LOW);
}

void set_color(int r, int b, int g) {
  digitalWrite(redLEDpin, r);
  digitalWrite(blueLEDpin, b);
  digitalWrite(greenLEDpin, g);
}

String ontvang_BT_signaal() {
  String boodschap = "";
  while (bluetooth.available())
  {
    char c = bluetooth.read();
    boodschap += c;
    delay(10);
  }
  return boodschap;
}
