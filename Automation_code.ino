#include <string.h>
#include <DHT.h>
#include <Servo.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Servo servo1;

char Incoming_value[20];
int Room = 13; 
int Kitchen = 12;
int Fan = 6;
int TempHum = 5;
int Buzzer = 8;
int ldr_pin = 7;
const int ldr_led = 11;
int trig1 = 4;
int echo1 = 3;
int trig2 = 10;
int echo2 = 9;
int park = 2;
int servo1_pin = A0;

int duration1 = 0, dist1 = 0;
int duration2 = 0, dist2 = 0;

void setup() {
  pinMode(Room, OUTPUT);
  pinMode(Kitchen, OUTPUT);
  pinMode(Fan, OUTPUT); 
  pinMode(TempHum, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(ldr_pin,INPUT);
  pinMode(ldr_led,OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  servo1.attach(servo1_pin);
  servo1.write(180);
  pinMode(park, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (Serial.available() > 0 ) {
    memset(Incoming_value, 0, sizeof(Incoming_value));
    Serial.readBytesUntil('\n', Incoming_value, sizeof(Incoming_value) - 1);
    Serial.println(Incoming_value);
    
    if (strcasecmp(Incoming_value , "room on") == 0) { 
      Serial.println(strcasecmp(Incoming_value , "room on"));
      digitalWrite(Room, HIGH);
    }  
    else if (strcmp(Incoming_value, "room out") == 0) {
      Serial.println(strcasecmp(Incoming_value , "room out"));
      digitalWrite(Room, LOW); 
    }
    else if (strcasecmp(Incoming_value, "kitchen on") == 0) { 
      Serial.println(strcasecmp(Incoming_value , "kitchen on"));
      digitalWrite(Kitchen, HIGH);
    }
    else if (strcasecmp(Incoming_value, "kitchen out") == 0) {
      Serial.println(strcasecmp(Incoming_value , "kitchen out"));
      digitalWrite(Kitchen, LOW);  
    }       
    else if (strcasecmp(Incoming_value, "fan on") == 0) { 
      Serial.println(strcasecmp(Incoming_value , "fan on"));
      digitalWrite(Fan, HIGH);
    }
    else if (strcasecmp(Incoming_value, "fan out") == 0) {
      Serial.println(strcasecmp(Incoming_value , "fan out"));
      digitalWrite(Fan, LOW);}
  }
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  {if (!isnan(temperature) && !isnan(humidity)) {
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" *C");
    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println(" %");
    if (temperature > 57) {
      digitalWrite(Buzzer, HIGH);
    } else {
      digitalWrite(Buzzer, LOW);
    }
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
  delay(1000);
  }
  {
    if( digitalRead( ldr_pin ) == 1){
      digitalWrite( ldr_led,HIGH);
   }
   else{
      digitalWrite( ldr_led , LOW);
   }
   Serial.println( digitalRead( ldr_pin ));
   delay(100);
  }
  {
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  pinMode(echo1, INPUT);
  duration1 = pulseIn(echo1, HIGH);
  dist1 = (duration1 * 0.034) / 2; 

  // Second ultrasonic sensor
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  pinMode(echo2, INPUT);
  duration2 = pulseIn(echo2, HIGH);
  dist2 = (duration2 * 0.034) / 2;

  if (dist1<5){
    digitalWrite(park, HIGH);
    delay(100);
  }
  else{
    digitalWrite(park,LOW);
  }
  if (dist1 < 5 && dist2 < 5) {
    Serial.println("Both sensors detect objects. Door won't open.");
  } else {
    if (dist2 < 5) {
      Serial.println("Object detected by second sensor. Door will open.");
      servo1.write(180); 
      delay(2000); 
    } else {
      Serial.println("No object detected. Door will remain closed.");
      servo1.write(0); 
      delay(1000);}
    }
  }
}
