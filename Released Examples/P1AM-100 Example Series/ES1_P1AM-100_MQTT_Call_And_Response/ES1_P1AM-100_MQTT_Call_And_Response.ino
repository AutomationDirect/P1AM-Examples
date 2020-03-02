/*  P1AM Example Series #1 - MQTT Call and Response
 * 
 *  This example uses an MQTT broker to update the outputs of a P1-08TRS
 *  to the inputs of a P1-08SIM. You can easily switch these out for any
 *  discrete input or output module.
 * 
 *  I used shiftr.io for this example. This is a free MQTT broker that provides
 *  nice visualisation and is great for testing. If you want to use a different broker,
 *  just update the broker string to the proper URL and update any login credentials
 *  
 *  Both the sending and receiving portions are included in this code, but these could
 *  easily be separated out into separate P1AM units or web interfaces. 
 *  
 *  With a little bit of modification, you can turn this example into a remote monitoring 
 *  solution or combine it with Modbus TCP and connect an aging PLC to the cloud.
 * 
 * 
 * 
 *  Written by FACTS Engineering
 *  Copyright (c) 2019 FACTS Engineering, LLC
 *  Licensed under the MIT license.
 */


#include <P1AM.h>
#include <ArduinoMqttClient.h>
#include <Ethernet.h>


channelLabel TRS = {1,0}; //P1-08TRS Slot 1. Channel = 0 means we will be using the bitmapped method.
channelLabel SIM = {2,0}; //P1-08SIM Slot 2. Channel = 0 means we will be using the bitmapped method.

EthernetClient client;
MqttClient mqttClient(client);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  // P1AM-ETH have unique MAC IDs on their product label
const char broker[]    = "broker.shiftr.io";  // MQTT Broker URL
int port = 1883;
uint8_t lastSentReading = 0; //Stores last Input Reading sent to the broker

void setup() {
  Serial.begin(115200);
  while(!P1.init());  //Wait for module sign-on
  Ethernet.init(5);   //CS pin for P1AM-ETH
  Ethernet.begin(mac);  // Get IP from DHCP
  
  mqttClient.setUsernamePassword("username", "password");  // Username and Password tokens for Shiftr.io namespace. These can be found in the namespace settings.
  Serial.print("Connecting to the MQTT broker: ");
  Serial.println(broker);
  while (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  mqttClient.subscribe("InputReading"); //Subscribe to "InputReading" topic
}

void loop() {
  //Sending Updates
  uint8_t inputReading = P1.readDiscrete(SIM); //Check inputs right now
  if(inputReading != lastSentReading){  // If the state doesn't match the last sent state, update the broker
    mqttClient.beginMessage("InputReading");  //Topic name
    mqttClient.print(inputReading); //Value to send
    mqttClient.endMessage();
    lastSentReading = inputReading; //Update our last sent reading
    Serial.println("Sent " + (String)inputReading + " to broker");
  }

  //Receiving updates
  int mqttValue = checkBroker();  //Check for new messages
  if(mqttValue != -1){  // -1 means we didn't get a new message
    P1.writeDiscrete(mqttValue, TRS); //If we get a new message update the TRS
  }
}

int checkBroker(){
  String mqttMessage = "";
  int messageValue = 0;

  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.print("Received a message with topic ");
    Serial.println(mqttClient.messageTopic());
    if(mqttClient.messageTopic() == "InputReading"){
      while (mqttClient.available()){
         mqttMessage +=(char)mqttClient.read(); //Add all message characters to the string
      }     
      messageValue =  mqttMessage.toInt();  //convert ascii string to integer value
    }
  }
  else{
    messageValue =  -1; //If we didn't receive anything set our value to -1. Since our SIM 
                        //value can't be -1, this makes it easy to filter out later
  }
  return messageValue;
}
