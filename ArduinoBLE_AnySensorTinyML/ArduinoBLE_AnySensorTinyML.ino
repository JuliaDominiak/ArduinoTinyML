#include <Arduino_APDS9960.h>

#define BTN_PIN             2        
#define NUM_SAMPLES         30
#define SAMPLING_PERIOD_MS  100

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
}

void loop() {
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b;
  unsigned long timestamp;
  unsigned long start_timestamp;

  while (digitalRead(BTN_PIN) == 1);
  
  Serial.println("timestamp,r,g,b");
  
  start_timestamp = millis();
  for (int i = 0; i < NUM_SAMPLES; i++) {
    timestamp = millis();
    while (! APDS.colorAvailable()) {
    delay(5);
  }
    APDS.readColor(r, g, b);

   Serial.print(timestamp - start_timestamp);
    Serial.print(",");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);

    while (millis() < timestamp + SAMPLING_PERIOD_MS);
  }

  Serial.println();

  while (digitalRead(BTN_PIN) == 0);
  delay(100);
}
