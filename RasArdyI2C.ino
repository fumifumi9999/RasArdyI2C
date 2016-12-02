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

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Timer3.attachInterrupt(fastHandler);
  Timer4.attachInterrupt(normalHandler);
  Timer5.attachInterrupt(slowHandler);
  Timer3.start(100);      //100us as Super fast timer
  Timer4.start(10000);    //10ms  as Main control timer
  Timer5.start(1000000);   //100ms as Variable timer

  Wire1.begin(SLAVE_ADDRESS);
  Wire1.onReceive(receiveData);
  Wire1.onRequest(sendData);

  pinMode(ForRaspiTriggerPin, OUTPUT);
}

void fastHandler() {
}

void normalHandler() {
  //Serial.print(Wire1.available());

}

void slowHandler() {
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

void loop() {
}


void sendData() {
  //byte testByte = 0xa2;
  //sendByteData(testByte);

  //word testWord = 1234;
  //word testWord = 0x3344;
  //sendWordData(testWord);

  //byte testByteArray[] = {0,1,2,3,4};
  //byte testByteArray[] = {0x0,0x1,0x2,0x3,0x4};
  //sendSomeByteData(testByteArray,sizeof(testByteArray));//sizeof may be heavy

  //word testWordArray[] = {0000,1000,2000,3000,4000};
  //word testWordArray[] = {0x0000,0x1000,0x2000,0x3000,0x4000};
  //sendSomeWordData(testWordArray, sizeof(testWordArray)); //sizeof() may be heavy

  Serial.println("called sendData");
}
void receiveData(int byteCount) {
  if (receiveCmdData() == 0x1) {  // 0x1 means that Master(Raspi) receives from Slave(Arduino)
    Serial.println("Arduino Send");
  } else {  // 0x0 means that Master(Raspi) sends to Slave(Arduino)
    //byte Byte = receiveByteData();
    //Serial.println(Byte, HEX);

    //word Word = receiveWordData();
    //Serial.println(Word);
    //Serial.println(Word, HEX);

    //byte Array[5] = {0};
    //receiveSomeByteData(Array);
    //for (int i = 0; i < 5; i++) {
    //  Serial.println(Array[i]);
    //  //Serial.println(Array[i], HEX);
    //}

    word Array[4] = {0};
    receiveSomeWordData(Array, sizeof(Array)/4);//sizeof is heavy
    for (int i = 0; i < 4; i++) {
      Serial.println(Array[i]);
    //  Serial.println(Array[i], HEX);
    }

    Serial.println("Arduino Receive");
  }
}




