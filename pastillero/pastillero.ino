#include <RTClib.h>

RTC_DS3231 rtc;

int led1Pin = 2;
int led2Pin = 3;
int led3Pin = 4; 
int led4Pin = 5;

int buttonPin = 6;
bool buttonPressed = false;

int buzzerPin = 7;

//funcion del parlante 

void setup() {
  Wire.begin();
  rtc.begin();

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  DateTime now = rtc.now();

  int activationHour, activationMinute;
  
  switch (now.hour()) {
    case 8:
      if(now.minute() == 30){
        digitalWrite(led1Pin, HIGH);
        //parlante
      }
      break;
    case 12:
      if(now.minute() == 15){
        digitalWrite(led2Pin, HIGH);
        //parlante
      }
      break;
    case 16:
      if(now.minute() == 30){
        digitalWrite(led3Pin, HIGH);
        //parlante
      }
      break;
    case 20:
      if(now.minute() == 15){
        digitalWrite(led4Pin, HIGH);
        //parlante
      }
      break;
    default:
      activationHour = -1; 
      activationMinute = -1;
      break;
  }

  //falta la parte de presionar el botón para apagar todo o que pase un minuto (quizas con contadores en el switch)

  delay(60000);
}

