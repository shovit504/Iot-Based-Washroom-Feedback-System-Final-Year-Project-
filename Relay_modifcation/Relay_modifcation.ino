#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>


int trigPin = 7;
int echoPin = 6;
int Relay = 1;


int duration = 0;
int distance = 0;

void setup() 
{
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  
  pinMode(Relay , OUTPUT);

  
  Serial.begin(9600);

}

void loop()
{
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;

  if ( distance <= 0 )  // set value when you want to turn OFF water pump
  {

    digitalWrite(Relay, LOW);
  }
  else if ( distance >= 1 )   // set value when you want to turn ON water pump
  {

    digitalWrite(Relay, HIGH);
  }
  
  delay(500);
}
