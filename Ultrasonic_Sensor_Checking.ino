const int trigPin = 33;
const int echoPin = 32;

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
 duration = pulseIn(echoPin, HIGH);
  
  
  distanceCm = duration ;
  
  Serial.print("Distance in (cm): ");
  Serial.println(distanceCm);
  
  
  delay(1000);
}