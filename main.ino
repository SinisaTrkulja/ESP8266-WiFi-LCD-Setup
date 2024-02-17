#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

static const char* aqi = "http://api.airvisual.com/v2/city?city=YourCity&state=TheStateYourCityIsIn&country=TheCountryYourStateIsIn&key=YOUR_REGISTERED_API_KEY";
static const char* time_url = "http://worldtimeapi.org/api/timezone/TheContinentYourCityIsIn/YourCity";


// This is how I mapped my pins, you might map yours any other way so long as you connect them the right way
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;


// Interval between subsequent http requests
const int TIME_TO_SLEEP = 10 * 60 * 1000;
 
// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(D1, D0, D4, D5, D6, D7);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("NameOfYourWiFiAP", "WifiPassword");

  lcd.print("Connecting");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (i % 4 == 0) { 
      lcd.clear();
      lcd.print("Connecting");
    }
    delay(500);
    lcd.print(".");
    i++;
  }
  lcd.clear();
  lcd.print("Connected!");
  delay(1000);
  
}
 
void loop() {
  WiFiClient client;
  HTTPClient http;

  // JSON structs to which we'll deserialize our data
  JsonDocument aqi_doc;
  JsonDocument time_doc;
  
  lcd.clear();
  http.begin(client, aqi);
    
  // Send HTTP GET request
  // We have to set this in order for the deserializeJson() to work with http.getStream()
  http.useHTTP10(true);
  int httpResponseCode_aqi = http.GET();
  
  if (httpResponseCode_aqi==200) {
    http.begin(client, time_url);
    int httpResponseCode_time = http.GET();
    
    if (httpResponseCode_time==200) {

      deserializeJson(aqi_doc, http.getStream());
      deserializeJson(time_doc, http.getStream());
      
      int aqius = aqi_doc["data"]["current"]["pollution"]["aqius"];
      const char* time_data = time_doc["datetime"];
      int year, month, day, hour, minute, second;
      sscanf(time_data, "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
      
      lcd.printf("AQI: %d", aqius);
      lcd.setCursor(0, 1);
      lcd.printf("At %d:%s%d", hour, minute < 10 ? "0" : "", minute);
      Serial.println(aqius);
    } else {
      lcd.printf("Error time: %d", httpResponseCode_time);
      Serial.print("Error code: ");
      Serial.println(httpResponseCode_time);
    }
  } else {
    lcd.printf("Error aqi: %d", httpResponseCode_aqi);
    Serial.print("Error code: ");
    Serial.println(httpResponseCode_aqi);
  }
  // Free resources
  http.end();
  delay(TIME_TO_SLEEP);
}
