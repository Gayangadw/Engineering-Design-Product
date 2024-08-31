#define BLYNK_TEMPLATE_ID "TMPL680pd7D6s"
#define BLYNK_TEMPLATE_NAME "smart waste bin"
#define BLYNK_AUTH_TOKEN "SStmM8ms52BYB3zgj7PfimzCw8C81TiV"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Pixel";
char pass[] = "11345678";


const int trigPin = 32;
const int echoPin = 33;

Servo servo;
long duration;
float distanceCm;
int binLevel = 0;

BlynkTimer timer;


void SMESensor()
{
  int ir = digitalRead(34);
  if (ir == HIGH)
  {    
    servo.write(90);
    for (int i = 0; i < 50; i++)
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  else
  {
    ultrasonic();
    delay(200);
  }
}

void ultrasonic()
{
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
  duration = pulseIn(echoPin, HIGH);
  
  
  distanceCm = duration * 0.034 / 2;
  
  
  binLevel = map(distanceCm, 50, 0, 0, 100); 
  
  
  Blynk.virtualWrite(V0, distanceCm); 
  Blynk.virtualWrite(V1, binLevel);   
}

void setup()
{
  Serial.begin(115200); 
  servo.attach(13);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run();
}
