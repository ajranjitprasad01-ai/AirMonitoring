////////////////////////////////// IoT ////////////////////////////////////
#define BLYNK_TEMPLATE_ID "TMPL3hugw-zrg"
#define BLYNK_TEMPLATE_NAME "Robot"
#define BLYNK_AUTH_TOKEN "WoRrVA_tVTVAdeYDrLyYxTbjO6tjSBgX"

#define BLYNK_PRINT Serial                 // uncoment this for IoT debugging 
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "robot";                            // wifi hotspot name
char pass[] = "12345678";                          // wifi hotspot password 

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(10, 11);               // RX, TX
ESP8266 wifi(&EspSerial);

BlynkTimer timer;


int f,b,l,r;


BLYNK_WRITE(V0)
{
  f = param.asInt(); // assigning incoming value from pin V0 to a variable
}


BLYNK_WRITE(V1)
{
  b = param.asInt(); // assigning incoming value from pin V1 to a variable
}



BLYNK_WRITE(V3)
{
  r = param.asInt(); // assigning incoming value from pin V3 to a variable
}


//////////////////////////////////////////////////////////////////////////////

#define methane     A0
#define carbon_mono A1

int ch4,co;

////////////////////////////////// DC MOTOR ////////////////////////////////////

#define motor1_A  2
#define motor1_B  3

#define motor2_A  4
#define motor2_B  5



void setup()
{
 
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);


  Serial.begin(9600);
  EspSerial.begin(9600);
  delay(100);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, send_parameters);

 }
 

void loop()
{
 
  Blynk.run();
  timer.run();
  

 if(f == HIGH)
 forward();

 if(b == HIGH)
 backward();

 if(l == HIGH)
 left();

 if(r == HIGH)
 right();

 if((f == LOW)&&(b == LOW)&&(l == LOW)&&(r == LOW))
 halt();

}






void forward()
{
  digitalWrite(motor1_A,LOW);
  digitalWrite(motor1_B,HIGH);
  digitalWrite(motor2_A,LOW);
  digitalWrite(motor2_B,HIGH);
}


void backward()
{
  digitalWrite(motor1_A,HIGH);
  digitalWrite(motor1_B,LOW);
  digitalWrite(motor2_A,HIGH);
  digitalWrite(motor2_B,LOW);
}

void right()
{
  digitalWrite(motor1_A,HIGH);
  digitalWrite(motor1_B,LOW);
  digitalWrite(motor2_A,LOW);
  digitalWrite(motor2_B,HIGH);
}

void left()
{
  digitalWrite(motor1_A,LOW);
  digitalWrite(motor1_B,HIGH);
  digitalWrite(motor2_A,HIGH);
  digitalWrite(motor2_B,LOW);
}

void halt()
{
  digitalWrite(motor1_A,LOW);
  digitalWrite(motor1_B,LOW);
  digitalWrite(motor2_A,LOW);
  digitalWrite(motor2_B,LOW);
}


void send_parameters()
{
ch4 = analogRead(methane);
co = analogRead(carbon_mono);
co = co-30;
ch4 = ch4-130;

Blynk.virtualWrite(V2, ch4);
Blynk.virtualWrite(V4, co);
}
