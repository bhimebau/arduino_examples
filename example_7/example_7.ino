#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>

// #define GET_FROM_INSTRUCTOR
// #define FEED_ID 
// #define API_KEY " "

#define THRESHOLD 475
int ledPin = 2;
int sensorPin = A0;

// Your Xively key to let you upload data
char xivelyKey[] = API_KEY;

//datastreams
char lightsensor_feed[] = "lightsensor";
char sensor_override_feed[] = "sensor_override";

XivelyDatastream datastreams[] = {
  XivelyDatastream(lightsensor_feed, strlen(lightsensor_feed), DATASTREAM_FLOAT),
  XivelyDatastream(sensor_override_feed, strlen(sensor_override_feed), DATASTREAM_FLOAT),
};

// Finally, wrap the datastreams into a feed
XivelyFeed feed(FEED_ID, datastreams, 2);
EthernetClient client;
XivelyClient xivelyclient(client);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {129, 79, 243, GET_FROM_INSTRUCTOR};
byte iudns[] = {129, 79, 1, 1};
byte gw[] = {129, 79, 243, 1};

float sensorval = 0.0;

void setup() {
  Serial.begin(9600);  
  Ethernet.begin(mac,ip, iudns, gw);
  pinMode(ledPin, OUTPUT);
  delay(1000);
}

void loop() {
  int getReturn = xivelyclient.get(feed, xivelyKey);    //get data from xively
  if(getReturn > 0){
    Serial.println("lightsensor");
    Serial.println(feed[0]);
    Serial.println("sensor_override");
    Serial.println(feed[1]);
  }
  else { 
    Serial.println("HTTP Error");
  }

 float sensorOverride = datastreams[1].getFloat();
  
  int sensorValue = analogRead(sensorPin);
  datastreams[0].setFloat(sensorValue);
  xivelyclient.put(feed, xivelyKey);
  if (sensorOverride>0.0) {
     digitalWrite(ledPin, HIGH);  
     Serial.print("OVERRIDE ENABLED\n");  
   }
   else if (sensorValue > THRESHOLD) {
     digitalWrite(ledPin, LOW);
     Serial.print("DAY\n");
   }
   else {
     digitalWrite(ledPin, HIGH);
      Serial.print("NIGHT\n"); 
   }
     
   delay(15000);
}





