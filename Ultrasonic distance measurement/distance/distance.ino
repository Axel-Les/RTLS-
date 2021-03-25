
void setup(void) {
  // put your setup code here, to run once:
 pinMode(16,OUTPUT);//trigger
 pinMode(17,INPUT);//echo

}


void loop() {
  delay(10);
  Serial.begin(115200);
  digitalWrite(16,HIGH);//trigger high
  delayMicroseconds(1);
  digitalWrite(16,LOW);
  delayMicroseconds(1);
  float time,distance;
  time=pulseIn(17,HIGH);
  distance = time / 58.2;// s=v*t; s=(t/2)*344m/s; s=(t/2)*0.0344; s=t/58.1
  if(distance > 100) {
    float distanc;
  distanc = distance / 100;
 
  Serial.print(distanc);
  Serial.println(" M");
 
  } else {
 
  Serial.print(distance);
  Serial.println(" cm");
  }


}//
