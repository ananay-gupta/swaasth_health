
#define BLYNK_TEMPLATE_ID "TMPL1rwsHkLh"
#define BLYNK_DEVICE_NAME "IOT Based Health Monitoring System "
#define BLYNK_AUTH_TOKEN "4NFZzThvWfDpS65W2AQ3XXczD-kTYa0K"

#define BLYNK_PRINT Serial
#define shutdown_pin 10 

int value = 0;


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"
#include "DHT.h"


double bt=0.0,ot=0.0,h=0.0;
int sp=0,bp=0;


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
DHT dht(0, DHT11);

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "cabb";
char pass[] = "123456789";

BlynkTimer timer;

PulseOximeter pox;
void onBeatDetected()
{
    //Serial.println("Beat!");
}

void myTimer() 
{
  
  Blynk.virtualWrite(V3, bt);
  Blynk.virtualWrite(V4, ot);
  Blynk.virtualWrite(V5, sp);
  Blynk.virtualWrite(V6, bp);
}


void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);
  mlx.begin();
  pox.begin();
  dht.begin();
  pox.setOnBeatDetectedCallback(onBeatDetected);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, myTimer); 

  

 
}

void loop()
{
    if((digitalRead(D5) == 1)||(digitalRead(D6) == 1))
  {
    Serial.println("leads off!");
    digitalWrite(shutdown_pin, LOW); //standby mode
    value=0;
  }
  else 
  {
    digitalWrite(10, HIGH); //normal mode
    digitalWrite(shutdown_pin, HIGH); //normal mode
    value = analogRead(A0);
    value = map(value, 250, 400, 0, 100); //to flatten the ecg values a bit
    delay(1);
  }
   pox.update();
  sp=pox.getSpO2();
  bp=pox.getHeartRate();
  h = dht.readHumidity();
  ot=mlx.readAmbientTempC();
  bt=mlx.readObjectTempC();
  Blynk.run();
  
   Blynk.virtualWrite(V8,value);
   Blynk.virtualWrite(V9, h);

   timer.run(); 
   
}
