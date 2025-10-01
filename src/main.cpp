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

void loop() {
    unsigned long currentMillis = millis();

    int power = 0;

    if (currentMillis >= 30000) {
        power = 50;
        analogWrite(L298N_PIN, power);
    }

    if (currentMillis - previousMillis >= interval) {
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
