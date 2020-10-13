/*
 * Base_controll
 * V0.93
 * Platform:- NodeMCU ESP8266
 * Google Assistant + Amazon Alexa Control
 * Code by:- Yash Mukhija & Pushan Singh
*/


///////////Import libraries and dependancies block START/////////////

#include <Arduino.h>              //import arduino basic library 
#include <ESP8266WiFi.h>          //import ESP8266 libraries
#include "Adafruit_MQTT.h"        //import adafruit MQTT libraries <last positive on v1.03.1>
#include "Adafruit_MQTT_Client.h" //import adafruit MQTT client libraries 
#include <ESP8266WiFiMulti.h>     //import ESP8266 multi wifi library for setup
#include <WebSocketsClient.h>     //including arduino web sockets for webhooks connection 
#include <ArduinoJson.h>          //including arduino Json for json compatibility <last positive on v5.13.5>
#include <StreamString.h>         // including stream string for connection stream

///////////Import libraries and dependancies block END/////////////



///////////Setup ESP8266wifi Multi library START/////////////

ESP8266WiFiMulti WiFiMulti; //making objects
WebSocketsClient webSocket; 
WiFiClient client;

///////////Setup ESP8266wifi Multi library END//////////////



///////////Declaring Pins for espmodule START//////////////

int Relay1 = 16; //light
int Relay2 = 5;  //fan
int Relay3 = 4;  //projector
int Relay4 = 0;  //AC

///////////Declaring Pins for espmodule END/////////////



///////////MQTT server SETUP module START//////////////

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "pushanyash"
#define MQTT_PASS "aio_dhPx62gjwS2plrp232GldzE2yye6"

///////////MQTT server SETUP module END//////////////



///////////WiFi Setup START/////////////

#define MyApiKey "f7c99b33-2b1d-47fe-90a0-c2f2b9969ad0" // Using Api key from sinric dashboard
#define MySSID "Yash1" // your Wifi network SSID
#define MyWifiPassword "123456789" // your Wifi network password

///////////WiFi Setup END/////////////



///////////MQTT client SETUP module START//////////////

Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Set up the feed you're subscribing to
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Light");
Adafruit_MQTT_Subscribe Fan = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Fan");
Adafruit_MQTT_Subscribe Projector = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Projector");
Adafruit_MQTT_Subscribe AC = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/AC");

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

///////////MQTT client SETUP module END//////////////




///////////Sinric connection module START//////////////

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void setPowerStateOnServer(String deviceId, String value);
void setTargetTemperatureOnServer(String deviceId, String value, String scale);

///////////Sinric connection module END//////////////



///////////Alexa Turn-ON module START//////////////

void turnOn(String deviceId) {
  if (deviceId == "5eba6fba9edee6138562179b")      // Device ID of first device LIGHT
  {  
    Serial.print("Turn on device id: "); //update log
    Serial.println(deviceId);            //update log
    digitalWrite(Relay1, LOW);           //Active low logic
  } 
  else if (deviceId == "5eba70879edee61385621956") // Device ID of second device FAN
  { 
    Serial.print("Turn on device id: "); //update log
    Serial.println(deviceId);            //update log
    digitalWrite(Relay2, LOW);           //Active low logic
  }
  else if (deviceId == "5eba70ad9edee613856219ae") // Device ID of third device PROJECTOR
  { 
    Serial.print("Turn on device id: "); //update log
    Serial.println(deviceId);            //update log
    digitalWrite(Relay3, LOW);           //Active low logic
  }
  else if (deviceId == "5eba71889edee61385621ae7") // Device ID of fourth device AC
  { 
    Serial.print("Turn on device id: "); //update log
    Serial.println(deviceId);            //update log
    digitalWrite(Relay4, LOW);           //Active low logic
  }
  else {
    Serial.print("Turn on for unknown device id: ");//Default case
    Serial.println(deviceId);            //Update log
  }     
}

///////////Alexa Turn-ON module END//////////////



///////////Alexa Turn-OFF module START//////////////

void turnOff(String deviceId) {
   if (deviceId == "5eba6fba9edee6138562179b")      // Device ID of first device LIGHT
   {  
     Serial.print("Turn off Device ID: "); //update log
     Serial.println(deviceId);             //update log
     digitalWrite(Relay1, HIGH);           //Active low logic
   }
   else if (deviceId == "5eba70879edee61385621956") // Device ID of second device FAN
   { 
     Serial.print("Turn off Device ID: "); //update log
     Serial.println(deviceId);             //update log
     digitalWrite(Relay2, HIGH);           //Active low logic
  }
  else if (deviceId == "5eba70ad9edee613856219ae") // Device ID of third device PROJECTOR
   { 
     Serial.print("Turn off Device ID: "); //update log
     Serial.println(deviceId);             //update log
     digitalWrite(Relay3, HIGH);           //Active low logic
  }
   else if (deviceId == "5eba71889edee61385621ae7") // Device ID of fourth device AC
   { 
     Serial.print("Turn off Device ID: "); //update log
     Serial.println(deviceId);             //update log
     digitalWrite(Relay4, HIGH);           //Active low logic
  }
  else {
     Serial.print("Turn off for unknown device id: ");//Default case
     Serial.println(deviceId);             //Update Log
  }
}

///////////Alexa Turn-OFF module END//////////////



///////////Alexa GET command Module START//////////////

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) { //using webSockets to access sinric
  switch(type) {    // Check Connection
    case WStype_DISCONNECTED: 
      isConnected = false;    //update connection variable
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n"); //update log
      break;
    case WStype_CONNECTED: {  
      isConnected = true;     //update connection variable
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload); //update log
      Serial.printf("Waiting for commands from sinric.com ...\n");       //update log 
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload); //WEBSOCKET to get payloads
       
          
        DynamicJsonBuffer jsonBuffer; 
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     // Get Device ID
        String action = json ["action"];         // Get Command
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);  //call to turn on
            } else {
                turnOff(deviceId); //call to turn off
            }
        }
        else if (action == "SetTargetTemperature") { // set temp command
            String deviceId = json ["deviceId"];     
            String action = json ["action"];
            String value = json ["value"];
        }
        else if (action == "test") { //Ping sinric
            Serial.println("[WSc] received test command from sinric.com"); //update log
        }
      }
      break;
    case WStype_BIN: //get binarry 
      Serial.printf("[WSc] get binary length: %u\n", length); //update log
      break;
  }
}

///////////Alexa GET command Module END//////////////



//////////Setup Block START//////////////

void setup()
{
  Serial.begin(115200); // Set BAUD rate for esp8266


  
//////////WiFi connection module START//////////////

  WiFiMulti.addAP(MySSID, MyWifiPassword); 
  Serial.println();
  Serial.print("Connecting to Wifi: "); //Update Log
  Serial.println(MySSID); //Update Log

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500); //wait 5 seconds
    Serial.print("."); //Update Log
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println(""); //Update Log
    Serial.print("WiFi connected. "); //Update Log
    Serial.print("IP address: "); //Update Log
    Serial.println(WiFi.localIP()); //Update Log
  }



  Serial.println("OK!"); //Update Log

//////////WiFi connection module END//////////////



  //Subscribe to the onoff feed
  
   mqtt.subscribe(&Light);     //Subscribe to Light feed
   mqtt.subscribe(&Fan);       //Subscribe to Fan feed
   mqtt.subscribe(&Projector); //Subscribe to Projector feed
   mqtt.subscribe(&AC);        //Subscribe to AC feed
   
   // server address, port and URL
   
  webSocket.begin("iot.sinric.com", 80, "/"); 

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets



//////////Pinmode Setup START//////////////

   pinMode(Relay1, OUTPUT); //Light
   pinMode(Relay2, OUTPUT); //Fan
   pinMode(Relay3, OUTPUT); //Projector
   pinMode(Relay4, OUTPUT); //AC
   
//////////Pinmode Setup END//////////////



//////////Initialize Relays START//////////////

  digitalWrite(Relay1, HIGH); //Active low logic
  digitalWrite(Relay2, HIGH); //Active low logic
  digitalWrite(Relay3, HIGH); //Active low logic
  digitalWrite(Relay4, HIGH); //Active low logic
  
//////////Initialize Relays END//////////////


}

//////////Setup Block END//////////////



//////////LOOP Block START//////////////

void loop()
{
  
  
  MQTT_connect(); //call function to connect to mqtt feed
  
  //Read from our subscription queue until run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(100)))
  {
    //If it is in here, a subscription updated...
    if (subscription == &Light)
    {
      //Print the new value to the serial monitor
      Serial.print("Light ");
      Serial.println((char*) Light.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Else, turn it off.
      if (!strcmp((char*) Light.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(Relay1, LOW);
      }
      else
      {
        digitalWrite(Relay1, HIGH);
      }
    }
    if (subscription == &Fan)
    {
      //Print the new value to the serial monitor
      Serial.print("FAN ");
      Serial.println((char*) Fan.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Else, turn it off.
      if (!strcmp((char*) Fan.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(Relay2, LOW);
      }
      else
      {
        digitalWrite(Relay2, HIGH);
      }
    }
    if (subscription == &Projector)
    {
      //Print the new value to the serial monitor
      Serial.print("Projector ");
      Serial.println((char*) Projector.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Else, turn it off.
      if (!strcmp((char*) Projector.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(Relay3, LOW);
      }
      else
      {
        digitalWrite(Relay3, HIGH);
      }
    }
     if (subscription == &AC)
    {
      //Print the new value to the serial monitor
      Serial.print("AC ");
      Serial.println((char*) AC.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Else, turn it off.
      if (!strcmp((char*) AC.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(Relay3, LOW);
      }
      else
      {
        digitalWrite(Relay3, HIGH);
      }
    }
  }
   webSocket.loop(); // call function
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night.
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}

//////////LOOP Block END//////////////



//////////MQTT Connection function START//////////////
void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(500);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         //kill connection and wait for WDT to reset
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
 


 


}

//////////MQTT Connection function END//////////////



//////////Set power function START//////////////

void setPowerStateOnServer(String deviceId, String value) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}

//////////Set power function END//////////////



//////////Set temprature function START//////////////

void setTargetTemperatureOnServer(String deviceId, String value, String scale) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["action"] = "SetTargetTemperature";
  root["deviceId"] = deviceId;
  
  JsonObject& valueObj = root.createNestedObject("value");
  JsonObject& targetSetpoint = valueObj.createNestedObject("targetSetpoint");
  targetSetpoint["value"] = value;
  targetSetpoint["scale"] = scale;
   
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}

//////////Set temprature function END//////////////


/****************************************************************END_OF_CODE************************************************************/
