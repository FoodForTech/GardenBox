/**
  Garden Box

  Electronically managed garden box

  created Wed. May 31st, 2017
  by Don Johnson
*/

#define SOIL_MOISTURE_PIN 0
#define WATER_PUMP_RELAY_PIN 8
#define LDR_SENSOR_PIN 1

// Moisture Sensor
int soilValue;
int avgSoilValue;

// Sensor rate
int count;
int readRate;

// Water Pump Relay (Low Level Trigger)
bool isPumpOn;

// Light Relay

void setup() {
  // Serial Monitor
  Serial.begin(9600);

  // Soil Moisture Sensor
  soilValue = 0;
  avgSoilValue = 0;
  count = 0;
  readRate = 50;
  isPumpOn = false;

  // Water Pump Relay
  pinMode(WATER_PUMP_RELAY_PIN, OUTPUT);
  digitalWrite(WATER_PUMP_RELAY_PIN, HIGH);
}

void loop() {
  soilValue += analogRead(SOIL_MOISTURE_PIN);
  if (count > readRate) {
    int avgSoilValue = soilValue / count;
    soilValue = 0;
    count = 0;
    Serial.print("LDR: ");
    Serial.print(analogRead(LDR_SENSOR_PIN));
    Serial.print(", ");

    Serial.print("Soil Moisture ");
    if (avgSoilValue >= 430) {
      Serial.print("Dry: ");
      switchWaterPumpRelay(true);
      readRate = 5;
    } else if (avgSoilValue >= 350 && avgSoilValue < 430) {
      Serial.print("Good: ");
      switchWaterPumpRelay(false);
      readRate = 50;
    } else if (avgSoilValue >= 260 && avgSoilValue < 350) {
      Serial.print("Wet: ");
      switchWaterPumpRelay(false);
      readRate = 50;
    }
    Serial.print(avgSoilValue);
    Serial.print(", ");

    if (isPumpOn) {
      Serial.print("Pump: ON, ");
    } else {
      Serial.print("Pump: OFF, ");
    }
    Serial.print("Read Rate: ");
    Serial.println(readRate);
  }
  count++;
  delay(100);
}

void switchWaterPumpRelay(bool isOn) {
  if (isOn && !isPumpOn) {
    digitalWrite(WATER_PUMP_RELAY_PIN, LOW);
    isPumpOn = true;
  } else if (!isOn && isPumpOn) {
    digitalWrite(WATER_PUMP_RELAY_PIN, HIGH);
    isPumpOn = false;
  }
}

