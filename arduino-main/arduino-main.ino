// Include required libraries
#include <SoftwareSerial.h>

// Define Tx & Rx Port where SIM800L Module connected with Arduino
int txPort = 5;
int rxPort = 2;
String msg;

// Create SIM SERIAL
SoftwareSerial simSerial(txPort, rxPort);

void setup() {
  Serial.begin(9600);
  simSerial.begin(9600);
  Serial.println("Sim Initializing...");
  simSerial.println("AT");
  updateSerial();
  simSerial.println("AT+CMGF=1");
  updateSerial();
  simSerial.println("AT+CMGS=\"0xxxxxxxxx\"");
  updateSerial();
  simSerial.print("Hi from NezukoBot 2FA SMS Verify!");
  updateSerial();
  simSerial.write(26);
}

void loop() {
}

void readSerialData(){
  msg = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

void sendData() {
  //write data
  Serial.print("Arduino received : ");
  Serial.print(msg);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    simSerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(simSerial.available()) 
  {
    Serial.write(simSerial.read());//Forward what Software Serial received to Serial Port
  }
}
