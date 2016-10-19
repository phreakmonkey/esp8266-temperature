/*****
 * Simple Temperature Sensor for the Adafruit Huzzah (or similar) ESP8266 board
 * Requires Dallas DS18B20 "One Wire" temperature sensor, wired to an input pin
 * (5 by default)
 * Requires OneWire and DallasTemperature arduino libraries (NOT MAX31850 ones!)
 * http://www.phreakmonkey.com
 */

#include<WiFiClient.h>
#include<ESP8266WiFi.h>
#include<WiFiUdp.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Network info
#define WIFI_SSID     "YourWiFiSSID"
#define WIFI_PASSWORD "YourWifiPassword"

WiFiUDP UDP;
unsigned int destport = 3141;
char destip[32] = "255.255.255.255";

// Amount to adjust temperature by in tenths of degrees F.
#define CALIB 0

// How often to transmit the temperature, in milliseconds (1000 = 1sec)
#define LOOPTIME 5000

// Pin number for OneWire.  (Warn: Will be held high at startup)
#define ONE_WIRE_BUS 5

#define STATUSLED 0
#define WIFILED 2

// Setup a oneWire bus instance & pass to Temperature library
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long counter = 0;

void setup(void)
{
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  pinMode(STATUSLED, OUTPUT);
  pinMode(WIFILED, OUTPUT);
  digitalWrite(STATUSLED, 1);
  digitalWrite(WIFILED, 1);
  // Connect to WiFi
  wifiConnect();

  // Start up the library
  sensors.begin();
  processTemp();  // Once on startup
}

void loop(void)
{
  if (millis() - counter > LOOPTIME) {
    counter = millis();
    processTemp();
  }
}

void processTemp()
{ 
  float tempF = 0;
  int decplace = 0;
  char tempFstring[6];

  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures();

  // "ByIndex" references which sensor in the network to get the temp from.
  tempF = sensors.getTempFByIndex(0) * 10;
  tempF += CALIB;
  sprintf(tempFstring, "%d", (int)tempF);

  // LOL add period
  decplace = strlen(tempFstring);
  tempFstring[decplace + 1] = 0;
  tempFstring[decplace] = tempFstring[decplace-1];
  tempFstring[decplace-1] = '.';
  sendTemp(tempFstring);
}

void sendTemp(char *dstring)
{
  // Construct and send the UDP packet
  digitalWrite(WIFILED, 0);
  UDP.beginPacket(destip, destport);
  UDP.write(dstring, sizeof(dstring));
  UDP.endPacket();
  yield();
  digitalWrite(WIFILED, 1);
  return;
}

void wifiConnect()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(STATUSLED, !digitalRead(STATUSLED)); // Blink Status LED while connecting
      delay(200);      
    }
    digitalWrite(STATUSLED, 0);
}
