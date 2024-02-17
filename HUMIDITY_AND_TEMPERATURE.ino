// FOR HUMIDITY AND TEMPERATURE SENSOR
#include<DHT.h>
#define type DHT11
int sensepin = A0;  // to read analog value
DHT ht(sensepin , type);
float humidity;
float tempc;
float tempF;
int wait = 100; 
//FOR LCD 
#include<LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 =10;
int d6 =11;
int d7 = 12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//dc mot0r
int speedpin = A1;
int dir1 = 2;
int dir2 = 3;
int speed = 0;
//control the speed of  motor using buttons
int b1 = 4;
int b1val;
//button2
int b2 = 5;
int b2val;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //SENSOR DHT11
  ht.begin();
  delay(wait);
  //LCD
  lcd.begin(16,2);
  //DC MOTOR
  pinMode(speedpin,OUTPUT);
  pinMode(dir1 , OUTPUT);
  pinMode(dir2 , OUTPUT);
  //BUTTONS
  pinMode(b1 , INPUT);
  pinMode(b2 , INPUT);
  digitalWrite(b1,HIGH);
  digitalWrite(b2,HIGH);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //read from sensor
  humidity = ht.readHumidity();
  tempc    = ht.readTemperature();
  tempF    = ht.readTemperature(true);
  //print on serial monitor
  Serial.print("humidity");
  Serial.print(  humidity);
  Serial.print("  Temperature c:");
  Serial.print(tempc);
  Serial.print("C");
  Serial.print("  Temperature F:");
  Serial.print(tempF);
  Serial.println("F");
  //print on lcd
  lcd.setCursor(0,0);
  lcd.print("Humidity :");
  lcd.print(humidity);
  delay(wait);
  lcd.setCursor(0,1);
  lcd.print("Temperature:");
  lcd.print(tempc);
  delay(wait);
  lcd.print("c");
  lcd.clear();
  //DC MOTOR
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  analogWrite(speedpin,speed);
  //button
  b1val = digitalRead(b1);
  b2val = digitalRead(b2);
 
  if(b1val == 0) // button1
  {
    speed = speed +10; // if buton1 pressed every time motor speed will increase by 10
    delay(wait);
  }
  // button 2 we can used to decrease the speed of the motor
 
  if(b2val == 0) // button1
  {
    speed = speed - 10; // if buton1 pressed every time motor speed will decrease by 10
  }
  //CASE FOR BUTTON1
 
  if(speed > 255)
  {
     speed = 255;
  }
  
  if(speed == 10)
  {
    speed == 100;
  }
 if(speed == 0)
  {
    analogWrite(speedpin , 0);
  }
  if(speed>0)
  {
    //clockwise
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  analogWrite(speedpin,speed);
 }
 //CASE FOR BUTTON 2
 if(speed < 255)
  {
     speed = -255;
  }
  
  if(speed == -10)
  {
    speed == -100;
  }
 if(speed<0)
  {
    //anti clock wise rotation of motor
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,LOW);
  analogWrite(speedpin,speed);
 }
}

   



