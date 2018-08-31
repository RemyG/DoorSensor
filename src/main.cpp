#include <Arduino.h>
#include <avr/sleep.h>

const int REED_PIN = 2; // Pin connected to reed switch
const int LED_PIN = 13; // LED pin - active-high

void wakeUp()
{
  Serial.println("Interrupt fired");
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(REED_PIN));
}

void sendOpenMessage()
{
  Serial.println("Open");
}

void sendCloseMessage()
{
  Serial.println("Closed");
}

void goToSleep()
{
  Serial.println("Go to sleep");
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(REED_PIN), wakeUp, CHANGE);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  delay(1000);
  sleep_cpu();
  Serial.println("Just woke up");
  if (digitalRead(REED_PIN) == LOW)
  {
    sendCloseMessage();
  }
  else
  {
    sendOpenMessage();
  }
}

void setup()
{
  Serial.begin(9600);
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  goToSleep();
}