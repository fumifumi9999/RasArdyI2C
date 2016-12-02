#include <Wire.h>
#include "RasArdyI2C.h"

void sendByteData(byte data) {
  Wire1.write(data);
}
void sendWordData(word data) {
  byte dataArray[2] = {highByte(data), lowByte(data)};
  Wire1.write(dataArray, 2);
}
void sendSomeByteData(byte data[], byte byteNum) {
  Wire1.write(data, byteNum);
}
void sendSomeWordData(word data[], byte WordNum) {
  byte ByteArray[WordNum * 2];
  for (int i = 0; i < WordNum; i++) {
    ByteArray[i * 2]   = highByte(data[i]);
    ByteArray[i * 2 + 1] = lowByte(data[i]);
  }
  Wire1.write(ByteArray, WordNum * 2);
}

byte receiveCmdData() {
  byte Cmd;
  Cmd = Wire1.read();
  return Cmd;
}

byte receiveByteData() {
  byte Byte;
  Byte = Wire1.read();
  //Serial.println(Byte);
  return Byte;
}
word receiveWordData() {
  word Word;
  byte ByteArray[2];
  int i = 0;
  while (Wire1.available()) {
    ByteArray[i] = Wire1.read();
    //Serial.println(ByteArray[i], HEX);
    i++;
  }
  Word = makeWord(ByteArray[0], ByteArray[1]);
  return Word;
}
void receiveSomeByteData(byte *ByteArray) {
  int i = 0;
  while (Wire1.available()) {
    ByteArray[i] = Wire1.read();
    //Serial.println(ByteArray[i],HEX);
    i++;
  }
}
void receiveSomeWordData(word *WordArray, byte WordNum) {
  byte ByteArray[WordNum * 2];
  int i = 0;
  while (Wire1.available()) {
    ByteArray[i] = Wire1.read();
    //Serial.println(ByteArray[i],HEX);
    i++;
  }
  for (i = 0; i < WordNum; i++) {
    WordArray[i] = makeWord(ByteArray[i * 2], ByteArray[i * 2 + 1]);
    //Serial.println(WordArray[i], HEX);
  }
}
