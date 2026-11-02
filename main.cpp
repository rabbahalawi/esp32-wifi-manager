#include <WiFi.h>
#include <WiFiManager.h>

const char* AP_NAME = "BCA188-ESP32-30";
#define RESET_PIN 0   // BOOT button = GPIO 0

WiFiManager wm;       // must be outside setup() so loop() can use it

void setup() {
  Serial.begin(115200);
  pinMode(RESET_PIN, INPUT_PULLUP);

  wm.setConfigPortalTimeout(180);

  if (!wm.autoConnect(AP_NAME)) {
    Serial.println("Connection failed");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (digitalRead(RESET_PIN) == LOW) {
    Serial.println("BOOT pressed... keep holding");
    unsigned long start = millis();
    while (digitalRead(RESET_PIN) == LOW) {
      if (millis() - start > 3000) {
        Serial.println("Resetting Wi-Fi settings...");
        wm.resetSettings();
        delay(1000);
        ESP.restart();
      }
    }
  }
}
