/* Remote control of an infrared heating panel with a DHT sensor and ESP8266.
   Remote measure of temperature and humidity.
  
   Version 1.0  5/3/2014  Version 1.0   Mike Barela for Adafruit Industries, many thanks!
   Version 2.0  23/10/2021 Jerry was here:
   - MAC in router sets fixed TCP/IP for the ESP8266
   - set on/off relais to switch on/off a heating or something another without any temperature control
   - LED green supply connect direct to 5V, LED blue WiFi on, LED red relais on
   - to do: program for a room fixed temperature  
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11           //sensor type DHT11
//#define DHTTYPE DHT22         //sensor type DHT22
#define DHTPIN  2               // Sensor read pin
#define relais_on         13    // Relais
#define led_wifi_ok       4     // blue
#define led_relais_on     5     // red

const char* ssid     = "xxxxxxxxxxx";
const char* password = "yyyyyyyyyyy";



ESP8266WebServer server(80);

// Initialize DHT sensor
// NOTE: For working with a faster than ATmega328p 16 MHz Arduino chip, like an ESP8266,
// you need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// This is for the ESP8266 processor on ESP-01
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266


float humidity, temp_f;  // Values read from sensor
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor


void setup(void)
{

  // Set pins for led-wifi, led-relais and relais to write and LOW.
 pinMode(led_wifi_ok, OUTPUT);
 digitalWrite(led_wifi_ok, LOW);

 pinMode(led_relais_on, OUTPUT);
 digitalWrite(led_relais_on, LOW);

 pinMode(relais_on, OUTPUT);
 digitalWrite(relais_on, LOW);

 
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(9600);  // Serial connection from ESP-01 via 3.3v console cable
  dht.begin();           // initialize temperature sensor

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());


  server.on("/", handle_root);          // send temperature and humidity from DHT sensor

  server.on("/on", handle_on);          // Relais for heating on

  server.on("/off", handle_off);        // Relais for heating off

  server.on("/top", handle_top);        // Control the heating for room teperature, eg. 20 C


  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{  server.handleClient();

 if (WiFi.status() == WL_CONNECTED) {  digitalWrite(led_wifi_ok, HIGH);  }
 
}
void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor
    previousMillis = currentMillis;

    
    // Sensor reading is slow up to 2 seconds, read twice!

    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature();         // Read temperature (Celsius)
    
    // if no data from sensor exit!
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}


void handle_root() {
 
   gettemperature();       // read sensor
    webString="Teplota:"+String(temp_f)+"C | Vlhkost:"+String((int)humidity)+"%";

    server.send(200, "text/plain", webString);            // send to someones browser when asked TCPIP of ESP8266

  delay(100);
}

 
 void handle_on(){          // Relais for heating on
    server.send(200, "text/plain", "Heating on");
    digitalWrite(led_relais_on, HIGH);  
    digitalWrite(relais_on, HIGH);  
 }

  void handle_off(){          // Relais for heating off
    server.send(200, "text/plain", "Heating off");
    digitalWrite(led_relais_on, LOW);
    digitalWrite(relais_on, LOW);  
 }

  void handle_top(){          // Control of room temperature  
    server.send(200, "text/plain", "Heating for room temperature 20 Grad C, not finished yet!");
  //  digitalWrite(led_relais_on, LOW);
  //  digitalWrite(relais_on, LOW);  
 }

 
