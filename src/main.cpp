#include <Arduino.h>

const byte LED_PIN = 5;        // Check your wiring! Previous header said 4, code says 5.
const int PWM_FREQ = 5000;     // 5 kHz frequency
const int PWM_RESOLUTION = 8;  // 8-bit resolution (0-255)
const int PWM_CHANNEL = 0;     // PWM channel

int duty_cycle = 0;    // Current brightness
int fadeAmount = 5;    // How many points to fade the LED by

void setup() {
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}

void loop() {
  ledcWrite(PWM_CHANNEL, duty_cycle);
  duty_cycle = duty_cycle + fadeAmount;
  if (duty_cycle <= 0 || duty_cycle >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30); 
}