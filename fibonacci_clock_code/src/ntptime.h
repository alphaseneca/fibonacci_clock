#include <arduino_secrets.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;
const long utcOffsetInSeconds = +20700; // UTC offset of Kathmandu +5:45 //https://www.epochconverter.com/timezones

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void fetchTime()
{
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());
}
