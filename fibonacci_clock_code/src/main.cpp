#include <Arduino.h>
#include <secrets.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <fibonacci_driver.h>
#include <ntptime.h>

// const char *ssid;
// const char *passphrase;

unsigned long currentTime1;
unsigned long timeElapsed1 = 0;
unsigned long currentTime2;
unsigned long timeElapsed2 = 0;
int hours;
int minutes;

const int resetpin = 1;

WiFiManager wm;
void setup(void)
{

  // Setup pins as Outputs
  pinMode(latchPin_CRGB, OUTPUT);
  pinMode(clockPin_CRGB, OUTPUT);
  pinMode(dataPin_CRGB, OUTPUT);
  // wm.resetSettings();
  // put your setup code here, to run once:
  Serial.begin(115200);
  bool wifistat;

  String SSID;
  String PASS;
  wifistat = wm.autoConnect("FiboArt Timepiece", "011235813");
  if (!wifistat)
  {
    Serial.println("Failed to connect");
  }

  else
  {
    Serial.println("connected...yeey :)");
    SSID = wm.getWiFiSSID();
    PASS = wm.getWiFiPass();
  }

  char ssid[SSID.length() + 1];
  char passphrase[PASS.length() + 1];

  strcpy(ssid, SSID.c_str());       //  Convert String to Char array
  strcpy(passphrase, PASS.c_str()); //  Convert String to Char array

  WiFi.begin(ssid, passphrase);

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

  if (digitalRead(resetpin) == HIGH)
  {
    wm.resetSettings();
    delay(2000);
    ESP.reset();
  }
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
