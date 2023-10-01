#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <LiquidCrystal.h>

const int servoPinTrash = 2;
const int servoPinRecycle = 13;
const int servoPinBio = 8;
Servo servoTrash;
Servo servoRecycle;
Servo servoBio;

const int neoPixelPin = 4;
Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(1, neoPixelPin, NEO_GRB + NEO_KHZ800);
const int ledTrashColor = neoPixel.Color(255, 0, 0); // Red
const int ledRecycleColor = neoPixel.Color(0, 255, 0); // Green
const int ledBioColor = neoPixel.Color(0, 0, 255); // Blue

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // Adjust pin numbers as needed

void setup() {
  Serial.begin(9600);
  servoTrash.attach(servoPinTrash);
  servoRecycle.attach(servoPinRecycle);
  servoBio.attach(servoPinBio);
  
  neoPixel.begin();
  neoPixel.show(); // Initialize all pixels to 'off'
  
  lcd.begin(16, 2); // Initialize the LCD with 16x2 characters
  lcd.setCursor(0, 0);
  lcd.print("Trash:");
  lcd.setCursor(0, 1);
  lcd.print("Recycle:");

  Serial.println("Connected to WiFi");
}

Servo servoTrash;
Servo servoRecycle;
Servo servoBio;

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.parseInt();
    Serial.println("Received command: " + String(incomingByte));
    
    if (incomingByte == 0) {
      for (pos = 0; pos <= 180; pos += 1) {
      servoTrash.write(pos);  // Set servo position
      delay(15);
    }
    delay(5000);           // Delay for smoother movement

  // Move the servo from 180 to 0 degrees
    for (pos = 180; pos >= 0; pos -= 1) {
      servoTrash.write(pos);  // Set servo position
      delay(15);
    }
    
    } 
    else if (incomingByte == 1) {
      for (pos = 0; pos <= 180; pos += 1) {
      servoRecycle.write(pos);  // Set servo position
      delay(15);
    }
    delay(5000);           // Delay for smoother movement

  // Move the servo from 180 to 0 degrees
    for (pos = 180; pos >= 0; pos -= 1) {
      servoRecycle.write(pos);  // Set servo position
      delay(15);
    }    
    }
    else if (incomingByte == 2) {
      for (pos = 0; pos <= 180; pos += 1) {
      servoBio.write(pos);  // Set servo position
      delay(15);
    }
    delay(5000);           // Delay for smoother movement

  // Move the servo from 180 to 0 degrees
    for (pos = 180; pos >= 0; pos -= 1) {
      servoBio.write(pos);  // Set servo position
      delay(15);
    }       
    }
  }
}

void openBox(Servo& servo, int ledColor, const char* boxName) {
  servo.write(90); // Rotate servo to open position (adjust as needed)
  neoPixel.setPixelColor(0, ledColor); // Turn on LED
  neoPixel.show();
  
  lcd.setCursor(strlen(boxName) + 1, 0);
  lcd.print("Opened");  
  delay(10000); // Keep the box open for 10 seconds
  
  servo.write(0); // Rotate servo to closed position
  neoPixel.setPixelColor(0, 0); // Turn off LED
  neoPixel.show();
  
  lcd.setCursor(strlen(boxName) + 1, 0);
  lcd.print("Closed ");
  lcd.setCursor(strlen(boxName) + 1, 1);
  lcd.print("       ");
}

