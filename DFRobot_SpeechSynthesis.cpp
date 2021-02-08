#include "DFRobot_SpeechSynthesis.h"
/*!
   @file DFRobot_SpeechSynthesis.h
   @brief Implementation of DFRobot_SpeechSynthesis class
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_SpeechSynthesis
*/

DFRobot_SpeechSynthesis::DFRobot_SpeechSynthesis(){

}

void DFRobot_SpeechSynthesis::speakElish(String word){
  uint16_t point = 0;
  _len=word.length();
  _unicode = (uint8_t *)malloc(_len+1);
  while(_index < _len){
  _unicode[point++] = (word[_index]&0x7f);
    _index++;
  }
  sendPack(START_SYNTHESIS1,_unicode,_len);

  wait();
  _index =0;
  _len = 0;

  if (_unicode!=NULL){
    free (_unicode);
    _unicode=NULL;
  }
}
void DFRobot_SpeechSynthesis::setVoice(uint8_t voc){
  String str="[v3]";
  if(voc > 9) voc = 9;
  str[2] = 48 + voc;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeed(uint8_t speed)
{
  String str="[s5]";
  if(speed > 9) speed = 9;
  str[2] = 48 + speed;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setTone(uint8_t tone){
  String str="[t5]";
  if(tone > 9) tone = 9;
  str[2] = 48 + tone;
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setSoundType(eSoundType_t type)
{
  String str;
  if(type == FEMALE1){
     str="[m3]";
  }else if(type == MALE1){
     str="[m51]";
  }else if(type ==FEMALE2){
     str="[m52]";
  }else if(type == MALE2){
     str="[m53]";
  }else if(type == DONALDDUCK){
     str="[m54]";
  }else if(type == FEMALE3){
     str="[m55]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setEnglishPron(eENpron_t pron)
{
  String str;
  if(pron == ALPHABET) {
     str="[h1]";
  }else if(pron ==WORD){
     str="[h2]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setDigitalPron(eDigitalPron_t pron){
  String str;
  if(pron == NUMBER) {
     str="[n1]";
  }else if(pron ==NUMERIC){
     str="[n2]";
  }else if(pron == AUTOJUDGED){
     str="[n0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeechStyle(eSpeechStyle_t style){
  String str;
  if(style == CATON) {
     str="[f0]";
  }else if(style ==SMOOTH){
     str="[f1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enablePINYIN(bool enable){
  String str;
  if(enable == true) {
     str="[i1]";
  }else if(enable ==false){
     str="[i0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setLanguage(eLanguage_t style){
  String str;
  if(style == CHINESEL) {
     str="[g1]";
  }else if(style ==ENGLISHL){
     str="[g2]";
  }else if(style == AUTOJUDGEL){
     str="[g0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setZeroPron(eZeroPron_t pron){
  String str;
  if(pron == ZREO) {
     str="[o0]";
  }else if(pron ==OU){
     str="[o1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setOnePron(eOnePron_t pron){
  String str;
  if(pron == YAO) {
     str="[y0]";
  }else if(pron ==CHONE){
     str="[y1]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setNamePron(eNamePron_t pron){
  String str;
  if(pron == NAME) {
     str="[r1]";
  }else if(pron ==AUTOJUDGEDN){
     str="[r0]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enableRhythm(bool enable){
  String str;
  if(enable == true) {
     str="[z1]";
  }else if(enable ==false){
     str="[z0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::reset(){

  speakElish("[d]");

}

void DFRobot_SpeechSynthesis::speak(String word){
  uint32_t uni=0;
  uint8_t utf8State = 0;
  DBG("\n");
  uint16_t point = 0;
  if (_utf8!=NULL){
    free (_utf8);
    _utf8=NULL;
  }DBG("\n");
  _len=word.length(); //总长度
  _utf8 = (uint8_t *)malloc(_len+1);
  if(_utf8==NULL){
   DBG("no memory");
   return;
  }
  DBG("_len=");DBG(_len);
  
  for(int i=0;i<=_len;i++){
    _utf8[i]= word[i]; //总的utf8码
  }
  DBG("\n");
  word="";
  uint16_t len1 = getWordLen();
  DBG("len1=");DBG(len1);
  _unicode = (uint8_t *)malloc(len1+1);
  while(_index < _len){
    if(_utf8[_index] >= 0xfc){
      utf8State = 5;
      uni = _utf8[_index]&1;
      _index++;
      for(uint8_t i=1;i<=5;i++){
        uni <<= 6;
        uni |= (_utf8[_index]&0x3f);
        utf8State--;
        _index++;
      }

    }else if(_utf8[_index] >= 0xf8){
      utf8State = 4;
      uni = _utf8[_index]&3;
      _index++;
      for(uint8_t i=1;i<=4;i++){
        uni <<= 6;
        uni |= (_utf8[_index]& 0x03f);
        utf8State--;
        _index++;
      }

      }else if(_utf8[_index] >= 0xf0){
        utf8State = 3;
        uni = _utf8[_index]&7;
        _index++;
        for(uint8_t i=1;i<=3;i++){
        uni <<= 6;
        uni |= (_utf8[_index]& 0x03f);
        utf8State--;
        _index++;
      }
      DBG(_index);DBG(uni);

	  }else if(_utf8[_index] >= 0xe0){
        curState = CHINESE;
        if((curState != lastState) && (lastState !=NONE)){
          lanChange = true;
		} else{
        utf8State = 2;
        DBG("index=");DBG(_index);
        uni = _utf8[_index]&15;
        _index++;
        DBG("uni=");DBG(uni);
        for(uint8_t i=1;i<=2;i++){
        uni <<= 6;
        uni |= (_utf8[_index]&0x03f);
        utf8State--;
        _index++;
         }
         if(_utf8[_index] == 239){
	//Serial.println("aaaa");
	      lanChange = true;
	     }
        lastState = CHINESE;
        DBG(_index);DBG(uni);
       _unicode[point++] = uni & 0xff;
       _unicode[point++] = uni >> 8  ;
	   //if(point ==  24) lanChange = true;
		}
      }else if(_utf8[_index] >= 0xc0){
        curState = CHINESE;
        if((curState != lastState) && (lastState !=NONE)){
          lanChange = true;

		}else{
        utf8State = 1;
        uni = _utf8[_index]&0x1f;
        _index++;
        for(uint8_t i=1;i<=1;i++){
        uni <<= 6;
        uni |= (_utf8[_index]& 0x03f);
        utf8State--;
        _index++;
      }
	  lastState = CHINESE;
       _unicode[point++] = uni & 0xff;
       _unicode[point++] = uni >> 8  ;
	   //if(point ==  24) lanChange = true;
		}
      }else if(_utf8[_index] <=0x80){
        curState = ENGLISH;
        if((curState != lastState) && (lastState !=NONE)){
          lanChange = true;

        }else{
       _unicode[point++] = (_utf8[_index]&0x7f);
       _index++;
       lastState = ENGLISH;
       if(/*(point ==  24) || */(_utf8[_index] == 0x20)|| (_utf8[_index] == 0x2c)) lanChange = true;
       }
      } 
   if(lanChange == true){
     if(lastState == CHINESE){
         sendPack(START_SYNTHESIS,_unicode,point);
		 wait();
	  }else if(lastState == ENGLISH){
         sendPack(START_SYNTHESIS1,_unicode,point);
		 wait();
	  }
	  lastState = NONE;
	  curState = NONE;
	  point = 0;
	  lanChange = false;
   }
  }
     if(lastState == CHINESE){
         sendPack(START_SYNTHESIS,_unicode,point);
        wait();
	  }else if(lastState == ENGLISH){
         sendPack(START_SYNTHESIS1,_unicode,point);
		 wait();
	  }
	  lastState = NONE;
	  curState = NONE;
	  point = 0;
	  lanChange = false;

  _index =0;
  _len = 0;
  
  if (_unicode!=NULL){
    free (_unicode);
    _unicode=NULL;
  }
  return ;

}
void DFRobot_SpeechSynthesis::wait(){
#if defined(NRF5) || defined(ARDUINO_SAM_ZERO)







while(readACK()!=0x4F)//等待语音播放完成
  {} 
#else 
while(readACK()!=0x41)//等待语音合成完成
  {}
while(readACK()!=0x4F)//等待语音播放完成
  {} 
  
#endif
  /*
readACK();
readACK();
readACK();
readACK();

*/
delay(10);
}
uint16_t DFRobot_SpeechSynthesis::getWordLen(){
  uint16_t index = 0;
  uint32_t uni=0;
  uint16_t length = 0;DBG("\n");
  DBG("len=");DBG(_len);
  while(index < _len){
    DBG("index=");DBG(index);
    if(_utf8[index] >= 0xfc){
      index++;
      for(uint8_t i=1;i<=5;i++){
        index ++;
      }
    length+=4;
    }else if(_utf8[index] >= 0xf8){
      index++;
      for(uint8_t i=1;i<=4;i++){
        index++;
      }
      length+=3;
      }else if(_utf8[index] >= 0xf0){
        index++;
        for(uint8_t i=1;i<=3;i++){
        index++;
      }
      length += 3;
      }else if(_utf8[index] >= 0xe0){
        index++;
        for(uint8_t i=1;i<=2;i++){
        index++;
      }
      length +=2;
      }else if(_utf8[index] >= 0xc0){

        index++;
        for(uint8_t i=1;i<=1;i++){
        index++;
      }
      length +=2;
      }else if(_utf8[index] <=0x80){
        index++;
        length++;
      } 
  }
  return length;
}

void DFRobot_SpeechSynthesis::stopSynthesis(){
  sendPack(STOP_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::pauseSynthesis(){
  sendPack(PAUSE_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::recoverSynthesis(){
  sendPack(RECOVER_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::sleep(){
  sendPack(ENTERSAVEELETRI);
}
void DFRobot_SpeechSynthesis::wakeup(){
  sendPack(WAKEUP);
}
void DFRobot_SpeechSynthesis::sendPack(uint8_t cmd,uint8_t* data,uint16_t len)
{
  
  uint16_t length = 0;
  uint8_t head[5] = {0};
  head[0] = 0xfd;
  switch(cmd){
    case START_SYNTHESIS:{
      length = 2 + len;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= START_SYNTHESIS;
      head[4]= 0x03;
      sendCommand(head,data,len);
   } break;
   case START_SYNTHESIS1:{
      length = 2 + len;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= START_SYNTHESIS;
      head[4]= 0x00;
      sendCommand(head,data,len);
   }
   break;
   default :{
      length = 1;
      head[1]= length >> 8;
      head[2]= length & 0xff;
      head[3]= cmd;
      sendCommand(head,4);
   }
   break;
  }
}
DFRobot_SpeechSynthesis_I2C::DFRobot_SpeechSynthesis_I2C(TwoWire *pWire, uint8_t address){
  _pWire = pWire;
  _deviceAddr = address;
}
DFRobot_SpeechSynthesis_I2C::~DFRobot_SpeechSynthesis_I2C(){
  //_pWire->setClock(100000);
}

bool DFRobot_SpeechSynthesis_I2C::begin()
{
uint8_t ack = 0;

    _pWire->begin();
    //_pWire->setClock(100000);
    uint8_t init = 0xAA;
    sendCommand(&init,1);
    delay(50);
    speakElish("[n1]");
    setVoice(5); 
    setSpeed(5); 
    setTone(5);  
    setSoundType(FEMALE1);
    setEnglishPron(WORD);
}
uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t *head,uint8_t *data,uint16_t length)
{
	 uint16_t lenTemp = 0;
//Serial.println(length);
  _pWire->beginTransmission(_deviceAddr);
  for(uint8_t i =0;i<5;i++){
     _pWire->write(head[i]);
  }
  _pWire->endTransmission();
  
  
  while(length){
     if(length > 28){
        lenTemp =28;
     } else {
        lenTemp = length;
    }

     _pWire->beginTransmission(_deviceAddr);
     for(uint8_t i =0;i<lenTemp;i++){
      _pWire->write(data[i]);
     }
     if( _pWire->endTransmission() != 0 ) {
         DBG("ERR_DATA_BUS");
         return ERR_DATA_BUS;
     }
     length -= lenTemp;
     data += lenTemp;
  }
#ifdef ENABLE_DBG
  Serial.println();
  for(uint8_t i =0;i<5;i++){
   Serial.print(head[i],HEX);
   Serial.print(" ");
  }
  for(uint8_t i =0;i<length;i++){
   Serial.print(data[i],HEX);
   Serial.print(" ");
  }
  Serial.println();
#endif
  // if( _pWire->endTransmission() != 0 ) {
      // DBG("ERR_DATA_BUS");
      // return ERR_DATA_BUS;
  // }


  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t *data,uint8_t length)
{


  _pWire->beginTransmission(_deviceAddr);
  for(uint8_t i =0;i<length;i++){
   _pWire->write(data[i]);
  }
  if( _pWire->endTransmission() != 0 ) {
      DBG("ERR_DATA_BUS");
      return ERR_DATA_BUS;
  }


  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_I2C::readACK(){

     uint8_t data = 0;
     uint8_t data1 =0;
     delay(20);

#if defined(NRF5) || defined(ARDUINO_SAM_ZERO)
     _pWire->requestFrom(_deviceAddr, 2);
     delay(10);
     data = _pWire->read();
	 data1 = _pWire->read();
     DBG(data,HEX);
	 DBG(data1,HEX);
	if(data == 0x4f || data1 == 0x4F)
        return 0x4f;
     else 
		 return data;
#else
   _pWire->requestFrom(_deviceAddr, 1);
   delay(10);
  if(_pWire->available()) {
     data = _pWire->read();
     DBG(data,HEX);
    }
   return data;

#endif
}

DFRobot_SpeechSynthesis_UART::DFRobot_SpeechSynthesis_UART(){


}

bool DFRobot_SpeechSynthesis_UART::begin(Stream &s){
   _s = &s;
   if(_s == NULL){
    return false;
   } else {
    speakElish("[n1]");
    setVoice(5); 
    setSpeed(5); 
    setTone(5);  
    setSoundType(FEMALE1);
    setEnglishPron(WORD);
    return true;
   }
   
}
uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t *head,uint8_t *data,uint16_t length)
{
   while (_s->available()) {
     _s->read();
    }


  for(uint8_t i =0;i<5;i++){
     _s->write(head[i]);
  }
  for(uint8_t i =0;i<length;i++){
   _s->write(data[i]);
  }
#ifdef ENABLE_DBG
  Serial.println();
  for(uint8_t i =0;i<5;i++){
   Serial.print(head[i],HEX);
   Serial.print(" ");
  }
  for(uint8_t i =0;i<length;i++){
   Serial.print(data[i],HEX);
   Serial.print(" ");
  }
  Serial.println();
#endif
  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t *data,uint8_t length)
{
  for(uint8_t i =0;i<length;i++){
   _s->write(data[i]);
  }
  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_UART::readACK(){

  uint8_t data = 0;
  delay(10);
  //DBG(data,HEX);
  if(_s->available()) {
     data = _s->read();
     //DBG(data,HEX);
  }
  //DBG(data,HEX);
  return data;

}
