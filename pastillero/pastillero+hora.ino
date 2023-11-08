#include <RTClib.h>
#include <WiFi.h>
#include "time.h"
#include "sntp.h"

const char* ssid       = "YOUR_SSID"; // nombre del wifi
const char* password   = "YOUR_PASS"; // contraseña del wifi

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = -10800;
const int   daylightOffset_sec = 3600;

const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

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
  // inicio del codigo del reloj
  Serial.begin(115200);

  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );

  /**
   * NTP server address could be aquired via DHCP,
   *
   * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
   * otherwise SNTP option 42 would be rejected by default.
   * NOTE: configTime() function call if made AFTER DHCP-client run
   * will OVERRIDE aquired NTP server address
   */
  sntp_servermode_dhcp(1);    // (optional)

  /**
   * This will set configured ntp servers and constant TimeZone/daylightOffset
   * should be OK if your time zone does not need to adjust daylightOffset twice a year,
   * in such a case time adjustment won't be handled automagicaly.
   */
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  /**
   * A more convenient approach to handle TimeZones with daylightOffset 
   * would be to specify a environmnet variable with TimeZone definition including daylight adjustmnet rules.
   * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
   */
  //configTzTime(time_zone, ntpServer1, ntpServer2);

  // final del codigo del reloj

  // inicio del codigo del wifi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // final del codigo del wifi

  
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
  //para mostrar la hora es printLocalTime(), toma un tiempo en sincronizar el tiempo

  delay(60000);
}