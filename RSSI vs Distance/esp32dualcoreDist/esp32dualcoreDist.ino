/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
#include <WiFi.h>
TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pins
//const int led1 = 2;
//const int led2 = 4;


void setup() {
  Serial.begin(115200); 
  //pinMode(led1, OUTPUT);
  //pinMode(led2, OUTPUT);
  pinMode(16,OUTPUT);//trigger
  pinMode(17,INPUT);//echo
  /*...............................................................................................................
*/
 char ssid[] = "Kapkan";   // your network SSID (name)
 char pass[] = "kindunicorn592";// your network password
 WiFi.mode(WIFI_STA);
 WiFi.disconnect();
 delay(100);

Serial.println("Setup done");
Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
      /*...............................................................................................................
*/
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
 xTaskCreatePinnedToCore(
                   Task1code,   /* Task function. */
                   "Task1",     /* name of task. */
                   4096,       /* Stack size of task in bytes */
                   NULL,        /* parameter of the task */
                   1,           /* priority of the task */
                   &Task1,      /* Task handle to keep track of created task */
                   1);          /* pin task to core 1 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    4096,       /* Stack size of task in bytes */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */
    delay(500); 
    Serial.println("\r\n");

 Serial.begin(115200);

    
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters )
{
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
      delay(10);
  //Serial.begin(115200);
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
  }
  vTaskDelay(10);
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
 

  // if you are connected, print out info about the connection:
 //int the received signal strength:
  //for(;;)
  long rssi = WiFi.RSSI();
  //Serial.print(ssid);
  //Serial.print(" : ");
  Serial.println(rssi);
  delay(10);
  


 vTaskDelay(10);
}

 

  

void loop() {
  
}
