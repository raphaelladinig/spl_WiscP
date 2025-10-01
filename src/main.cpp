#include "HardwareSerial.h"
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 2
#define L298N_PIN 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
    Serial.begin(9600);
    sensors.begin();
    pinMode(L298N_PIN, OUTPUT);
}

int power = 55;
void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        power += 40;
        if (power > 255) {
            power = 55;
        }

        analogWrite(L298N_PIN, power);
        previousMillis = currentMillis;

        sensors.requestTemperatures();
        float temperature = sensors.getTempCByIndex(0);

        Serial.print(currentMillis);
        Serial.print('\t');
        Serial.print(power);
        Serial.print('\t');
        Serial.println(temperature);
    }
}
