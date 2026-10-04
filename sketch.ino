#define BLYNK_TEMPLATE_ID "TMPL3HhI0PYn4"
#define BLYNK_TEMPLATE_NAME "kitchen safety monitoring"
#define BLYNK_AUTH_TOKEN "aMtnby1Nz1olz6kmgVo3Ov7R44mQ7j3G"         // from your device's Device Info tab

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ---------- WiFi settings ----------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---------- Pin setup ----------
#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ2_PIN 34
#define LED_PIN 2
#define BUZZER_PIN 5

DHT dht(DHTPIN, DHTTYPE);

// ---------- Thresholds ----------
const int GAS_WARNING = 3000;
const int GAS_DANGER  = 4000;
const float TEMP_WARNING = 35.0;
const float TEMP_DANGER  = 45.0;

unsigned long lastUpload = 0;
const unsigned long uploadInterval = 200; // Blynk can handle much faster updates than ThingSpeak

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();   // keeps the connection to Blynk.Cloud alive — must be called every loop

  int gasValue = analogRead(MQ2_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.println("Gas: " + String(gasValue) +
                  " | Temp: " + String(temperature) + " C" +
                  " | Humidity: " + String(humidity) + " %");

  String status = getStatus(gasValue, temperature);
  Serial.println("Status: " + status);

  handleAlert(status);

  if (millis() - lastUpload > uploadInterval) {
    sendToBlynk(gasValue, temperature, humidity, status);
    lastUpload = millis();
  }
}

String getStatus(int gas, float temp) {
  if (gas > GAS_DANGER || temp > TEMP_DANGER) {
    return "DANGER";
  } else if (gas > GAS_WARNING || temp > TEMP_WARNING) {
    return "WARNING";
  } else {
    return "SAFE";
  }
}

void handleAlert(String status) {
  if (status == "SAFE") {
    digitalWrite(LED_PIN, HIGH);
    delay(800);
    digitalWrite(LED_PIN, LOW);
    delay(800);
    noTone(BUZZER_PIN);
  } else if (status == "WARNING") {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
    noTone(BUZZER_PIN);
  } else { // DANGER
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  }
}

// Sends readings to Blynk's virtual pins — V0, V1, V2, V3 are just labeled
// "slots" you create on the Blynk.Cloud dashboard to hold each value
void sendToBlynk(int gas, float temp, float hum, String status) {
  Blynk.virtualWrite(V0, gas);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);
  Blynk.virtualWrite(V3, status);
}
