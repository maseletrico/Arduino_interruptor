#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library         
#else
#include <WiFi.h>      //ESP32 Core WiFi Library    
#endif

#if defined(ESP8266)
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#else
#include <WebServer.h> //Local WebServer used to serve the configuration portal ( https://github.com/zhouhan0126/WebServer-esp32 )
#endif

#include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal ( https://github.com/zhouhan0126/DNSServer---esp32 )
#include <WiFiManager.h>   // WiFi Configuration Magic ( https://github.com/zhouhan0126/WIFIMANAGER-ESP32 ) >> https://github.com/tzapu/WiFiManager (ORIGINAL)

const int LED = 5; //Define the led pin
const int TOUTCH = 4; //Define the toutch pin
const int RELE = 2; //Define the relay pin

bool totchState = false;
bool wifiConnected = false;

//variáveis para controle dentro do loop
bool stateLed = false;

void ICACHE_RAM_ATTR handleButtonInterrupt() {
  Serial.println("Toutch");
  unsigned long lastBtnPress;
  unsigned long actualMillis = millis();

  if (actualMillis - lastBtnPress > 500) {
    lastBtnPress = actualMillis; {
      stateLed = !stateLed;
      digitalWrite(LED, stateLed);
      digitalWrite(RELE, !stateLed);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  Serial.println("Start");
  setup_wifiManager();
  pinMode(LED, OUTPUT);
  pinMode(TOUTCH, INPUT);
  pinMode(RELE, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(TOUTCH), handleButtonInterrupt, HIGH);
}

void loop() {
  if (wifiConnected) {
    loop_wifi();
  }
}
