
#define BLYNK_TEMPLATE_ID "TMPL4Bd2n-76z"
#define BLYNK_TEMPLATE_NAME "Temp Hum"
#define BLYNK_AUTH_TOKEN "9wY92NwQlnK2TFQ9akL5u8gZTNpaZZtJ"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_SHTC3.h>



// Replace with your Blynk auth token, WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "FoxHome";
char pass[] = "ceco0804$";

Adafruit_SHTC3 shtc3;

BlynkTimer timer;

void sendSensorData() {
  sensors_event_t humidity, temp;
  
  // Read temperature and humidity from the sensor
  shtc3.getEvent(&humidity, &temp);

  if (!isnan(temp.temperature) && !isnan(humidity.relative_humidity)) {
    // Send data to Blynk
    Blynk.virtualWrite(V1, temp.temperature);
    Blynk.virtualWrite(V2, humidity.relative_humidity);
    
    // Print data to Serial Monitor
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println(" %");
  } else {
    Serial.println("Failed to read from SHTC3 sensor!");
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Initialize the SHTC3 sensor
  if (!shtc3.begin()) {
    Serial.println("Couldn't find SHTC3 sensor. Check wiring!");
    while (1);
  }
  Serial.println("SHTC3 sensor initialized successfully!");

  // Set a timer to send sensor data every second
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}