#define BLYNK_TEMPLATE_ID "TMPL3lPdSgRaM"
#define BLYNK_TEMPLATE_NAME "exhauster"
#define BLYNK_AUTH_TOKEN "GRQWgR10hEqytf5K4HzdQEEBhTm6soFJ"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN D5 // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define FAN_PIN D2 // FAN RELAY
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Itel vision 2S";
char pass[] = "31012004vnr";
float humDHT = 0;
float tempDHT = 0;
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(115200);
pinMode(FAN_PIN, OUTPUT);
digitalWrite(FAN_PIN, LOW);
Serial.println(F("DHTxx test!"));
dht.begin();
Blynk.begin( auth, ssid , pass );
}
void loop() {
Blynk.run();
// Wait a few seconds between measurements.
delay(2000);
// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
humDHT = dht.readHumidity();
// Read temperature as Celsius (the default)
tempDHT = dht.readTemperature();
// Check if any reads failed and exit early (to try again).
if (isnan(humDHT) || isnan(tempDHT)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
Serial.print(F("Temperature: "));
Serial.print(tempDHT);
Serial.print(F("°C "));
Serial.println();
Serial.print(F("Humidity: "));
Serial.print(humDHT);
Serial.println(F("%"));
// Debugging information for relay state
Serial.print("Relay State: ");
Serial.println(digitalRead(FAN_PIN));
// Compare Threshold value from Blynk and DHT Temperature value.
if (tempDHT > 31) {
 Serial.println("Fan On");
 } else {
 digitalWrite(D2, HIGH);
 Serial.println("Fan Off");
 }
 // Virtual write to Blynk
 Blynk.virtualWrite(V1, tempDHT);
 Blynk.virtualWrite(V2, humDHT);
}
