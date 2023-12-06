#include <RTClib.h>

struct Alarm {
  int hour;
  int minute;
  int pin;
};

RTC_DS3231 rtc;

const int PIN_BUTTON = 2;
bool buttonPressed = false;

const int PIN_LED1 = 19;
const int PIN_LED2 = 18;
const int PIN_LED3 = 5; 
const int PIN_LED4 = 13;
const int PIN_BUZZER = 14;

const int BUZZER_FREQUENCY = 500; 
const int CHANNEL = 0;
const int RESOLUTION = 8;

Alarm alarms[4] = {{8,0,PIN_LED1},{12,0,PIN_LED2},{19,31,PIN_LED3},{23,0,PIN_LED4}};

bool ledcAttach(uint8_t pin, uint32_t freq, uint8_t RESOLUTION);


void activateBuzzer() {
  ledcAttachPin(PIN_BUZZER, CHANNEL); 
  ledcSetup(CHANNEL, BUZZER_FREQUENCY, RESOLUTION); 
  ledcWrite(CHANNEL, 255);
}


void deactivateBuzzer() {
  ledcWrite(CHANNEL, 0); 
}


void removeAlerts() {
  deactivateBuzzer();
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, LOW);
  digitalWrite(PIN_LED3, LOW);
  digitalWrite(PIN_LED4, LOW);
}

void displayAlert(const int ledPin) {
   digitalWrite(ledPin, HIGH);
   activateBuzzer();
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();

    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);

  pinMode(PIN_BUTTON, INPUT_PULLUP);

  pinMode(PIN_BUZZER, OUTPUT);
  }

void loop() {
  DateTime now = rtc.now();

  for (Alarm alarm : alarms) {
    if (now.hour() == alarm.hour && now.minute() == alarm.minute) {
      displayAlert(alarm.pin);
    }
  }


  if (digitalRead(PIN_BUTTON) == LOW) {
    if (!buttonPressed) {
      removeAlerts();
      buttonPressed = true;
      delay(60000);
    }
  } else {
    buttonPressed = false; 
  }
}