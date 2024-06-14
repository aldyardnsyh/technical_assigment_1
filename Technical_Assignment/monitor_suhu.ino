#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

const char* ssid = "aldyardnsyh";
const char* password = "monitoringsuhu";

const char* serverName = "http://192.168.1.4:5000/sensor/data";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {

      String jsonPayload = "{\"temperature\":";
      jsonPayload += temperature;
      jsonPayload += ",\"kelembapan\":";
      jsonPayload += humidity;
      jsonPayload += ",\"timestamp\":\"";
      jsonPayload += millis();
      jsonPayload += "\"}";

      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(jsonPayload);

      if (httpResponseCode > 0) {
        String response = http.getString(); 
        Serial.println(httpResponseCode); 
        Serial.println(response); 
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      http.end(); 
    }

  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(5000); 
}
