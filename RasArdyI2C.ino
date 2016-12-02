#include <Arduino.h>
#include <RasArdyI2C.h>

#include <DueTimer.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04

word WordI2CSendArray[4];

int val = 0;
int ForRaspiTriggerPin = 2;
int ForRaspiToggle = 0;
int plus = 0;
int cmd = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Timer3.attachInterrupt(fastHandler);
  Timer4.attachInterrupt(normalHandler);
  Timer5.attachInterrupt(slowHandler);
  Timer3.start(100);      //100us as Super fast timer
  Timer4.start(10000);    //10ms  as Main control timer
  Timer5.start(1000000);   //1s as Variable timer

  Wire1.begin(SLAVE_ADDRESS);
  Wire1.onReceive(receiveData);
  Wire1.onRequest(sendData);

  pinMode(ForRaspiTriggerPin, OUTPUT);
}

void fastHandler() {
}

void normalHandler() {
  ForRaspiToggle ^= 1;
  digitalWrite(ForRaspiTriggerPin, ForRaspiToggle);

  val = analogRead(0);
  //  Serial.print("normal handler:");
  //  Serial.println(val);
  WordI2CSendArray[0] = val;
  WordI2CSendArray[1] = val + 100;
  WordI2CSendArray[2] = val + 200;
  WordI2CSendArray[3] = val + 300;
}

void slowHandler() {
}

void loop() {
}

void sendData() {
  //sendByteData(testByte);
  //sendWordData(testWord);
  //sendSomeByteData(testByteArray,sizeof(testByteArray));//sizeof may be heavy
  word testWordArray[] = {0x0000, 0x1111, 0x2222, 0x3333, 0x4444};
  sendSomeWordData(testWordArray, sizeof(testWordArray)); //sizeof() may be heavy

}
void receiveData(int byteCount) {
  cmd = receiveCmdData();
  if (cmd == 0x1) {  // 0x1 means that Master(Raspi) receives from Slave(Arduino)
    //Arduino Send
  } else {  // 0x0 means that Master(Raspi) sends to Slave(Arduino)
    //byte Byte = receiveByteData();
    //word Word = receiveWordData();
    //byte Array[5] = {0};
    //receiveSomeByteData(Array);
    word Array[4] = {0};
    receiveSomeWordData(Array, sizeof(Array)/4);//sizeof is heavy
    for(int i=0;i<4;i++){
      Serial.print(Array[i]);
      Serial.print(",");
    }
    Serial.println(++plus);
  }
}

