# Connect your ESP8266 to your WiFi, have it look up AQI data and print the results to a 16x2 LCD screen, hooked up without an I2C bus.

Because I was checking the AQI data for my city constantly on my phone and my laptop, I wanted to build this simple gadget and keep it in a visible place all the time.

I decided to publish this simple script and pinout in case anyone might find the schematic or (extremely simple) code helpful.

What you'll need:
* ESP-8266
* LCD 16x2
* Potentiometer
* Power supply
* Cables


Here's the pinout I used for reference, which I've found [here](https://www.circuitschools.com/interfacing-16x2-lcd-module-with-esp32-with-and-without-i2c/).

![image](https://github.com/SinisaTrkulja/ESP8266-WiFi-LCD-Setup/assets/120110398/2235e7d3-4e99-4d35-aff5-cfe9c252ad74)

An ESP-32 was used here instead of our ESP-8266 but that's of little importance as what counts is that the power and ground are hooked up correctly to both the potentiometer and the screen, the exact data buses need not match, as we can specify how we've mapped them in the source code.


How it looks in action (pardon the messy cable-work):
![6169DB42-A7F3-424A-8D7C-E2A41175FEF0](https://github.com/SinisaTrkulja/ESP8266-WiFi-LCD-Setup/assets/120110398/66405e92-e551-4162-a3c4-4e19ead7bf5b)
