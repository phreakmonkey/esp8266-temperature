# Q&D ESP8266 Temperature Sensor
## with client "catcher"

### Hardware:
- Adafruit Huzzah ESP8266 board (or equivalent)
- Dallas DS18B20 Temperature Sensor

### Dependencies
- Arduino 1.6+
- Libraries for ESP8266
- OneWire library
- DallasTemerature library
  
### Connecting:
- Connect DS18B20 to 3V, data pin 5, and GND (no resistor needed!)
- See DS18B20 pinout for details

### Configuring

See the #define lines in the top of the Arduino code for configuration notes.
Be sure to set you WiFi SSID and password, and any config changes needed for
your specific setup.

By default the ESP8266 sends the temperature to the broadcast (255.255.255.255)
address.  You can change this (and the UDP port number) as needed.

### Client
'''UDPCatcher.py''' is a basic listener for the UDP packets from the ESP8266.
Be sure to set the listening port number if you changed it in the sensor code.
