#include <SoftwareSerial.h>
SoftwareSerial SIM900(11,12);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

float latitude = 12.700070;
float longitude = 77.244822;

String long_lat;

String Link;
String SMS;

int eye=5;
int buzzer=4;
int relay=6;
int led=3;
int alcohol=8;
int seat=10;
int crash = 7;
 int count=0;  
 boolean state = true;


int get_location(String message){
  SIM900.print("ATD +91948149**** ;\r");
  delay(1000);
  SIM900.print("AT+CMGF=1\r");     // AT command to set SIM900 to SMS mode
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");       // Set module to send SMS data to serial out upon receipt
  delay(100);
    
  SIM900.println("AT+CMGF=1"); // Replace x with mobile number
  delay(1000);
  SIM900.println("AT+CMGS= \"+91948149****\"\r"); // Replace Number with mobile number
  delay(1000); 
  SIM900.println(message);// The SMS text you want to send
  delay(100);
  SIM900.println((char)26);// ASCII code of CTRL+Z 
}  


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SIM900.begin(9600);
  lcd.begin();
  lcd.backlight();
  
pinMode(eye,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(led,OUTPUT);
pinMode(alcohol,INPUT);
pinMode(seat,INPUT_PULLUP);
pinMode(crash,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
int ey=digitalRead(eye);
int alc=digitalRead(alcohol);
int seatb=digitalRead(seat);
int crash1=digitalRead(crash);
Serial.println(ey);
delay(500);
if (ey==0){  
   digitalWrite(buzzer,HIGH);
   digitalWrite(relay,LOW); 
   digitalWrite(led,HIGH); 
     lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Drowsiness detected");
   Serial.println("Alert: drowsiness detected");
   long_lat = String(float(latitude))+","+String(float(longitude));
   Link = "https://www.google.com/maps/search/?api=1&query="+String(long_lat);
   SMS = "Alert: Drowsiness detected "+ long_lat + " " + Link;//////////////////////////////SMS message
   Serial.println(SMS);
   get_location(SMS);
  } 
  
else if(alc==0)
{
    lcd.clear();
    lcd.setCursor(0,0);
   lcd.print("Alcohol detected");
     digitalWrite(buzzer,HIGH);
     digitalWrite(relay,LOW); 
      digitalWrite(led,HIGH); 
  }  
else if(seatb==1)
{  lcd.clear();
     lcd.setCursor(0,0);
   lcd.print("Seat belt detected");
     digitalWrite(buzzer,HIGH);
   digitalWrite(relay,LOW); 
  digitalWrite(led,HIGH);
    
}
else if(crash1==0)
{
  lcd.clear();
     lcd.setCursor(0,0);
   lcd.print("Crash detected");
     digitalWrite(buzzer,HIGH);
   digitalWrite(relay,LOW); 
  digitalWrite(led,HIGH);
    Serial.println("Alert: Crash detected");
  long_lat = String(float(latitude))+","+String(float(longitude));
   Link = "https://www.google.com/maps/search/?api=1&query="+String(long_lat);
   SMS = "Alert: Crash detected "+ long_lat + " " + Link;//////////////////////////////SMS message
   Serial.println(SMS);
   get_location(SMS);
}
     
 else
 {
   lcd.setCursor(0,0);
   lcd.print("Drowsiness Alert");
   lcd.setCursor(0,1);
   lcd.print("Detection system");
  digitalWrite(buzzer,LOW);
  digitalWrite(relay,HIGH); 
   digitalWrite(led,LOW); 
  }
 }
