/*!
   @file DFRobot_SpeechSynthesis.h
   @brief Basic structure of DFRobot_SpeechSynthesis class
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2020-08-17
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_SpeechSynthesis
*/

#ifndef DFROBOT_SPEECHSYNTHESIS_H
#define DFROBOT_SPEECHSYNTHESIS_H
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>
//#define ENABLE_DBG
// #include <SoftwareSerial.h>
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define I2C_ADDR               0x40  //i2c address
#define INQUIRYSTATUS          0x21
#define ENTERSAVEELETRI        0x88
#define WAKEUP                 0xFF

#define START_SYNTHESIS        0x01
#define START_SYNTHESIS1       0x02
#define STOP_SYNTHESIS         0x02
#define PAUSE_SYNTHESIS        0x03
#define RECOVER_SYNTHESIS      0x04

class DFRobot_SpeechSynthesis {
public:
  #define ERR_OK             0      //No error
  #define ERR_DATA_BUS      -1      //Data bus error
  #define ERR_IC_VERSION    -2      //Chip version does not match



  /**！
    Speech Synthesis style 
  */
  typedef enum{
    CATON,/**<Word by word>*/
    SMOOTH,/**<Fluently>*/
  } eSpeechStyle_t;
  
  /**
    Whether synthesize PinYin
  */
  typedef enum{
    PINYIN_ENABLE,/**<Synthesize PinYin>*/
    PINYIN_DISABLE,/**<Not>*/
  } ePinyin_t;
  
  /**
    Synthesize Arabic number, unit, special character into Chinese or English 
  */
  typedef enum{
    CHINESEL,/**<Chinese>*/
    ENGLISHL,/**<English>*/
    AUTOJUDGEL,/**<Auto Judge>*/
  } eLanguage_t;
  
  /**
   How to  read long numbers 
  */
  typedef enum{
    NUMBER,/**<Telephone number>*/
    NUMERIC,/**<Number>*/
    AUTOJUDGED,/**<Auto Judge>*/
  } eDigitalPron_t;
  
  /**
   How to read "0" 
  */
  typedef enum{
    ZREO,/**<Read as 'zero'>*/
    OU,/**<Read as'ou'>*/
  } eZeroPron_t;

  /**
    How to read "1" 
  */
  typedef enum{
    YAO,/**<Read as 'yao'>*/
    CHONE,/**<Read as 'yi'>*/
  } eOnePron_t;
  
  /**
   The function is only used for Chinese reading  
  */
  typedef enum{
    NAME,
    AUTOJUDGEDN,
  } eNamePron_t;
  
  /**
    Select sound type 
  */
  typedef enum{
    FEMALE1,/**<Female 1, recommended>*/
    MALE1,/**<Male 1, recommended>*/
    FEMALE2,/**<Female 2>*/
    MALE2,/**<Male 2>*/
    DONALDDUCK,/**<Donald Duck>*/
    FEMALE3,/**<Female 3>*/
  } eSoundType_t;

  /**
    How to read English 
  */
  typedef enum{
   ALPHABET,/**<Spell>*/
   WORD,/**<word>*/
  } eENpron_t;
  
  typedef enum{
    CHINESE,
    ENGLISH,
    NONE,
  } eState_t;
  
public:
  /**
     @brief Constructor 
     @param pWire I2C BUS pointer object， construct device, can pass parameter or not, default to Wire
     @param address 7bits I2C address, the first three bits determine the value of the address, default to 0x50
  */
  DFRobot_SpeechSynthesis();
  
  /**
     @brief Speech synthesis function 
     @param word Content to be synthesized, could be Chinese, English, Number, etc. 
  */
  void speak(String word);
  
  /**
     @brief Set sensor to sleep mode 
  */
  void sleep();
  
  /**
     @brief Wake up sensor from sleep mode 
  */
  void wakeup();
  
  /**
     @brief Set voice volume
     @param voc, Volume value(0-9)
  */
  void setVoice(uint8_t voc);
  
  /**
     @brief Set playback speed 
     @param speed, Speed value (0-9)
  */
  void setSpeed(uint8_t speed);

  /**
     @brief Set sound type 
     @param type(MALE:Male, FEMALE:Female, DONALDDUCK: Donaldduck)
  */
  void setSoundType(eSoundType_t type);

  /**
     @brief Set tone 
     @param tone, Tone value (0-9)
  */
  void setTone(uint8_t tone);

  /**
     @brief Set how to read English 
     @param pron(ALPHABET: letter, WORD: word)
  */
  void setEnglishPron(eENpron_t pron);
  
  /**
     @brief Reset settings to default 
  */
  void reset();
  
  /**
     @brief  The function is only used for Chinese reading
     @param enable(true,false)
  */
  void enableRhythm(bool enable);
  
  /**
     @brief Set how to read "1" in phone number 
     @param pron(YAO: read as "yao", CHONE: read as "yi")
  */
  void setOnePron(eOnePron_t pron);
  
  /**
     @brief Set whether to use surname reading principle mandatorily 
     @param pron(NAME: force, AUTOJUDGEDN: auto judge)
  */
  void setNamePron(eNamePron_t pron);
  
  /**
     @brief Set how to read "0" in phone number 
     @param pron(ZREO: read as "zero", OU: read as "ou")
  */
  void setZeroPron(eZeroPron_t pron);
  
  /**
     @brief  Synthesize Arabic number, unit, special character into Chinese or English 
     @param style(CHINESEL: Chinese, ENGLISHL: English, AUTOJUDGEL: Auto judge)
  */
  void setLanguage(eLanguage_t style);
  
  /**
     @brief Enable PinYin Synthesis 
     @param enable(true: enable, false: disable)
  */
  void enablePINYIN(bool enable);
  
  /**
     @brief Set synthesis style 
     @param enable(CATON: word by word, SMOOTH: fluently)
  */
  void setSpeechStyle(eSpeechStyle_t style);
  
  /**
     @brief Set how to read long numbers 
     @param pron(NUMBER: phone number, NUMERIC: number, AUTOJUDGED: Auto judge)
  */
  void setDigitalPron(eDigitalPron_t pron);
  
  /**
     @brief Stop synthesis 
  */
  void stopSynthesis();
  /**
     @brief Synthesis pause
  */
  void pauseSynthesis();

  /**
     @brief Recover synthesis 
  */
  void recoverSynthesis();
  
  /**
     @brief Wait for speech synthesis to complete 
  */
  void wait();
  
  /**
     @brief Synthesize English char string
  */
  void speakElish(String word);
private:


  uint8_t *_utf8;
  uint8_t *_unicode;
  uint16_t uniLen = 0;
  uint16_t _index=0;
  uint16_t _len=0;

  eState_t curState = NONE;
  eState_t lastState = NONE;
  bool lanChange = false;
  uint16_t getWordLen();
  virtual uint8_t readACK()= 0;
  void sendPack(uint8_t cmd,uint8_t* data =NULL,uint16_t len = 0);

  virtual uint8_t sendCommand(uint8_t *data,uint8_t length)=0;
  virtual uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length)=0;

};


class DFRobot_SpeechSynthesis_I2C :public DFRobot_SpeechSynthesis{
public:
  DFRobot_SpeechSynthesis_I2C(TwoWire *pWire = &Wire, uint8_t address = I2C_ADDR);
  ~DFRobot_SpeechSynthesis_I2C();
  bool begin();
private:
  uint8_t _deviceAddr;
  TwoWire *_pWire;
  //Stream none;
  uint8_t readACK();
  uint8_t sendCommand(uint8_t *data,uint8_t length);
  uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length);
};


class DFRobot_SpeechSynthesis_UART :public DFRobot_SpeechSynthesis{
public:
  DFRobot_SpeechSynthesis_UART();
  
  bool begin(Stream &s);

private:
  uint8_t readACK();
  uint8_t sendCommand(uint8_t *data,uint8_t length);
  uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length);
  
  Stream *_s;
  uint32_t _baudRate;
};







#endif
