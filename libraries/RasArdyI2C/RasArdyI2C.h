#ifndef _RasArdyI2C_h
#define _RasArdyI2C_h

void sendByteData(byte data);
void sendWordData(word data);
void sendSomeByteData(byte data[], byte byteNum);
void sendSomeWordData(word data[], byte WordNum);

byte receiveCmdData();
byte receiveByteData();
word receiveWordData();
void receiveSomeByteData(byte *ByteArray);
void receiveSomeWordData(word *WordArray, byte WordNum);

#endif
