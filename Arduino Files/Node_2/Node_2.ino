
#define BLYNK_TEMPLATE_ID "TMPL1rwsHkLh"
#define BLYNK_DEVICE_NAME "IOT Based Health Monitoring System "
#define BLYNK_AUTH_TOKEN "4NFZzThvWfDpS65W2AQ3XXczD-kTYa0K"

#define BLYNK_PRINT Serial



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 0, NEO_GRB + NEO_KHZ800);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "cabb";
char pass[] = "123456789";


int num = 0;
int oldVal = HIGH;
unsigned long startTime;
unsigned int seconds = 0;
boolean flag=false;

int valuee=0;

BlynkTimer timer;

float bt=0.0,ot=0.0;
int sp=0,bp=0,red=0,green=0,r=0;

BLYNK_WRITE(V3)
{
  bt = param.asDouble(); 
}

BLYNK_WRITE(V4)
{
  ot = param.asDouble(); 
}

BLYNK_WRITE(V5)
{
  sp = param.asInt(); 
}

BLYNK_WRITE(V6)
{
  bp = param.asInt(); 
}

void myTimer() 
{
 // printt();
//  if(bt>37 || sp<80 || bp < 60 || bp >100 || r>25)
//  {
//    pixels.setPixelColor(0, pixels.Color(255,0,0));
//    pixels.show();
//    digitalWrite(16,HIGH);
//    delay(2000);
//    digitalWrite(16,HIGH);
//    pixels.setPixelColor(0, pixels.Color(0,255,0));
//    pixels.show();
//  }
 
}

void printt(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Body Temp: ");
  lcd.setCursor(11,0);
  lcd.print(bt);
  lcd.setCursor(0,1);
  lcd.print("OUT Temp: ");
  lcd.setCursor(10,1);
  lcd.print(ot);
  delay(600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sp02: ");
  lcd.setCursor(6,0);
  lcd.print(sp);
  lcd.setCursor(12,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Beats: ");
  lcd.setCursor(7,1);
  lcd.print(bp);
  lcd.setCursor(12,1);
  lcd.print("bpm");
  
}


void setup()
{
 
  Serial.begin(115200);
  while (!Serial);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SWAASTH Health");
  lcd.setCursor(0,1);
  lcd.print("Monitor System");
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0,255,0));
  pixels.show();
//pinMode(16,OUTPUT); //buzzer
pinMode(2,INPUT); // respiration
//digitalWrite(16,LOW);
digitalWrite(2,HIGH);


Blynk.begin(auth, ssid, pass);
timer.setInterval(600L, myTimer); 
startTime = millis();

 
}

void loop()
{
   valuee=analogRead(A0);
   int val= digitalRead(2);
 if ( (val == LOW) && (oldVal == HIGH) ) 
  {
    ++num;
  delay(1000);
  }
  if ( millis() - startTime >= 1000 )
  {
    seconds++;
  if (seconds==10)
  {
    r=num;
    seconds=0;
    num=0;
  }
    startTime = millis();
  }
oldVal=val;
   
  Blynk.run();
   timer.run(); 
  Blynk.virtualWrite(V10, r);
  Blynk.virtualWrite(V7, valuee);
   
}
