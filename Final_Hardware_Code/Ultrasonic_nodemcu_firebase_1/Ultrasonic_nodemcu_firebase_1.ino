#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
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

#define FIREBASE_HOST "https://ultrasonic-sensor-98d22-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "kVH7zJeG8GQ1h4OPyT5JN4rVAZi02USqIqRRm5nn"
#define WIFI_SSID "Suvendu"
#define WIFI_PASSWORD "Prus@504"
 

FirebaseData firebaseData;

int trigPin = D1;
int echoPin = D2;
int trigPin1 = D3;
int echoPin1 = D4;                         
int WaterValue = D0; 
int WaterValue1 = D7; 
int WaterValue2 = D8; 
int WaterValue3 = D5;  
//int Relay = 6;                   
int GasValue;
                         
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
//  pinMode(Relay , OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connecting with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  sensorUpdate();
  sensorUpdate1();
//  Relay();
  Water_Sensor();
  Water_Sensor1();
  Water_Sensor2();
  Water_Sensor3();
  Gas_Sensor();

}

void sensorUpdate()
{
  long d,r;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  d = pulseIn(echoPin, HIGH);
  r = (d/2) / 29.1;

  Serial.print(r);

  Serial.println("cm");

  if(isnan(r))
  {
    Serial.print(F("Failed to read from FIRST ULTRASONIC SENSOR"));
    return;
  }


  if(Firebase.setFloat(firebaseData, "/Distance/cm", r))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 

}


void sensorUpdate1()
{
  long d1,r1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  d1 = pulseIn(echoPin1, HIGH);
  r1 = d1 / 58.2;

  Serial.print(r1);

  Serial.println("cm");

  if(isnan(r1))
  {
    Serial.print(F("Failed to read from FIRST ULTRASONIC SENSOR"));
    return;
  }


  if(Firebase.setFloat(firebaseData, "/Distance1/cm", r1))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 
//  if ( r1 <= 0 )  // set value when you want to turn OFF water pump
//  {
//
//    digitalWrite(Relay, LOW);
//  }
//  else if ( r1 >= 1 )   // set value when you want to turn ON water pump
//  {
//
//    digitalWrite(Relay, HIGH);
//  }
//  
//  delay(500);

}
//void Relay()
//{
//  long d1,r1;
//  digitalWrite(trigPin1, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin1, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin1, LOW);
//
//  d1= pulseIn(echoPin1, HIGH);
//  r1 = (d1/2) / 29.1;
//
//  Serial.print(r1);
//
//  Serial.println("cm");
//
//  if(isnan(r1))
//  {
//    Serial.print(F("Failed to read from SECOND ULTRASONIC SENSOR"));
//    return;
//  }
//
//
//  if(Firebase.setFloat(firebaseData, "/Distance1/cm", r1))
//  {
//    Serial.println("PASSED");
//    Serial.println("PATH: " + firebaseData.dataPath());
//    Serial.println("TYPE: " + firebaseData.dataType());
//    Serial.println("ETag: " + firebaseData.ETag());
//    Serial.println("------------------------------------------");
//    Serial.println();
//  }
//  else
//  {
//    Serial.println("FAILED");
//    Serial.println("REASON: " + firebaseData.errorReason());
//    Serial.println("------------------------------------------");
//    Serial.println();
//  } 
//  int duration = 0;
//  int distance = 0;
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);  
//  duration = pulseIn(echoPin, HIGH);
//  distance = duration/58.2;
//
//  if ( distance <= 0 )  // set value when you want to turn OFF water pump
//  {
//
//    digitalWrite(Relay, LOW);
//  }
//  else if ( distance >= 1 )   // set value when you want to turn ON water pump
//  {
//
//    digitalWrite(Relay, HIGH);
//  }
//  
//  delay(500);
//
//  Serial.print(distance);
//
//  Serial.println("cm");
//
//  if(isnan(distance))
//  {
//    Serial.print(F("Failed to read from SECOND ULTRASONIC SENSOR"));
//    return;
//  }
//
//
//  if(Firebase.setFloat(firebaseData, "/Distance1/cm", distance))
//  {
//    Serial.println("PASSED");
//    Serial.println("PATH: " + firebaseData.dataPath());
//    Serial.println("TYPE: " + firebaseData.dataType());
//    Serial.println("ETag: " + firebaseData.ETag());
//    Serial.println("------------------------------------------");
//    Serial.println();
//  }
//  else
//  {
//    Serial.println("FAILED");
//    Serial.println("REASON: " + firebaseData.errorReason());
//    Serial.println("------------------------------------------");
//    Serial.println();
//  } 
//}

void Water_Sensor()
{
  int value;

  value = digitalRead(WaterValue);

  Serial.print(value);


  if(isnan(value))
  {
    Serial.print(F("Failed to read from FIRST WATER SENSOR"));
    return;
  }
 
  if(Firebase.setFloat(firebaseData, "/Value/units", value))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 

}

void Water_Sensor1()
{
  int value1;

  value1 = digitalRead(WaterValue1);

  Serial.print(value1);


  if(isnan(value1))
  {
    Serial.print(F("Failed to read from FIRST WATER SENSOR"));
    return;
  }
 
  if(Firebase.setFloat(firebaseData, "/Value1/units", value1))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 

}

void Water_Sensor2()
{
  int value2;

  value2 = digitalRead(WaterValue2);

  Serial.print(value2);


  if(isnan(value2))
  {
    Serial.print(F("Failed to read from FIRST WATER SENSOR"));
    return;
  }
 
  if(Firebase.setFloat(firebaseData, "/Value2/units", value2))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 

}

void Water_Sensor3()
{
  int value3;

  value3 = digitalRead(WaterValue3);

  Serial.print(value3);


  if(isnan(value3))
  {
    Serial.print(F("Failed to read from FIRST WATER SENSOR"));
    return;
  }
 
  if(Firebase.setFloat(firebaseData, "/Value3/units", value3))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 

}
void Gas_Sensor()
{
  int gas_value;
  gas_value = analogRead(GasValue);


  Serial.print(gas_value);


  if(isnan(gas_value))
  {
    Serial.print(F("Failed to read from GAS SENSOR"));
    return;
  }

  if(Firebase.setFloat(firebaseData, "/Gas_Value/ppm", gas_value))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------------");
    Serial.println();
  } 
}
