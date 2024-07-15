#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <fibonacci_driver.h>
#include <ntptime.h>

unsigned long currentTime1;
unsigned long timeElapsed1 = 0;
unsigned long currentTime2;
unsigned long timeElapsed2 = 0;
int hours;
int minutes;
void setup(void)
{

  // Setup pins as Outputs
  pinMode(latchPin_CRGB, OUTPUT);
  pinMode(clockPin_CRGB, OUTPUT);
  pinMode(dataPin_CRGB, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // // Initialize SPI
  // SPI.begin();
  // SPI.setFrequency(1000000); // Set SPI frequency to 1 MHz

  // Initialize a NTPClient to get time
  timeClient.begin();
}

String inputString = "";     // A string to hold incoming data
bool stringComplete = false; // Whether the string is complete
// Reserve 200 bytes for the inputString
// inputString.reserve(200);
// Function to handle the input string
unsigned long tracktime;
void loop()
{
  // Check if the string is complete
  // if (stringComplete)
  // {
  //   // Call the function with the input string
  //   handleInput(inputString);
  //   // Clear the string
  //   inputString = "";
  //   stringComplete = false;
  // }

  currentTime1 = millis();
  if (currentTime1 - timeElapsed1 >= 10000)
  {
    timeElapsed1 = currentTime1;
    fetchTime();
    minutes = timeClient.getMinutes();
    minutes = minutes / 5;
    hours = timeClient.getHours();
    hours = (hours > 12) ? hours - 12 : hours;
  }
  displayTime(hours, minutes);
  // currentTime2 = micros();
  // if (currentTime2 - timeElapsed2 >= 100)
  // {
  //   timeElapsed2 = currentTime2;
  // }
  // int minutes = timeClient.getSeconds();
  // int hours = timeClient.getHours();
  // displayTime({(hours > 12 ? hours - 12 : hours)}, minutes / 5);
  // timeClient.update();
}
