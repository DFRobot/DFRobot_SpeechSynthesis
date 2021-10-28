/*!
 * @file DFRobot_SpeechSynthesis.h
 * @brief Basic structure of DFRobot_SpeechSynthesis class
 * @details Synthesize the sound you need, support Chinese, English
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-08-17
 * @url https://github.com/DFRobot/DFRobot_SpeechSynthesis
*/

#ifndef DFROBOT_SPEECHSYNTHESIS_H
#define DFROBOT_SPEECHSYNTHESIS_H
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define I2C_ADDR               0x40  //i2c address
#define INQUIRYSTATUS          0x21  //Check status
#define ENTERSAVEELETRI        0x88   
#define WAKEUP                 0xFF  //Wake-up command

#define START_SYNTHESIS        0x01  //Start synthesis command 0
#define START_SYNTHESIS1       0x02  //Start synthesis command 1
#define STOP_SYNTHESIS         0x02  //End speech synthesis
#define PAUSE_SYNTHESIS        0x03  //pause speech synthesis command
#define RECOVER_SYNTHESIS      0x04  //Resume speech synthesis commands

class DFRobot_SpeechSynthesis {
public:
  #define ERR_OK             0      //No error
  #define ERR_DATA_BUS      -1      //Data bus error
  #define ERR_IC_VERSION    -2      //Chip version does not match


  typedef struct
  {
    uint8_t ischar ;  
    uint16_t index;
    uint16_t length;
  
  }sSubMess_t;

  /**！
   *@enum eSpeechStyle_t Speech Synthesis style 
   */
  typedef enum{
    eCaton,/**<Word by word>*/
    eSmooth,/**<Fluently>*/
  } eSpeechStyle_t;
  
  /**
   *@enum ePinyin_t Whether synthesize PinYin
   */
  typedef enum{
    ePinyinEnable,/**<Synthesize PinYin>*/
    ePinyinDisable,/**<Not>*/
  } ePinyin_t;
  
  /**
   *@enum eLanguage_t Synthesize Arabic number, unit, special character into Chinese or English 
   */
  typedef enum{
    eChinesel,/**<Chinese>*/
    eEnglishl,/**<English>*/
    eAutoJudgel,/**<Auto Judge>*/
  } eLanguage_t;
  
  /**
   *@enum eDigitalPron_t How to  read long numbers 
   */
  typedef enum{
    eNumber,/**<Telephone number>*/
    eNumeric,/**<Number>*/
    eAutoJudged,/**<Auto Judge>*/
  } eDigitalPron_t;
  
  /**
   *@enum eZeroPron_t How to read "0" 
   */
  typedef enum{
    eZreo,/**<Read as 'zero'>*/
    eOu,/**<Read as'ou'>*/
  } eZeroPron_t;

  /**
   *@enum eOnePron_t How to read "1" 
   */
  typedef enum{
    eYao,/**<Read as 'yao'>*/
    eChone,/**<Read as 'yi'>*/
  } eOnePron_t;
  
  /**
   *@enum eNamePron_t The function is only used for Chinese reading  
   */
  typedef enum{
    eName,
    eAutoJudgedn,
  } eNamePron_t;
  
  /**
   *@enum eSoundType_t Select sound type 
   */
  typedef enum{
    eFemale1,    /**<Female 1, recommended>*/
    eMale1,      /**<Male 1, recommended>*/
    eMale2,      /**<Male 2>*/
    eFemale2,    /**<FEMALE 2>*/
    eDonaldDuck, /**<Donald Duck>*/
    eFemale3,    /**<Female 3>*/
  } eSoundType_t;

  /**
   *@enum eENpron_t How to read English 
   */
  typedef enum{
   eAlphabet,/**<Spell>*/
   eWord,/**<word>*/
  } eENpron_t;
  
  typedef enum{
    eChinese,
    eEnglish,
    eNone,
  } eState_t;
  
public:

  DFRobot_SpeechSynthesis();
  
  /**
   * @fn speak
   * @brief Speech synthesis function 
   * @param word Content to be synthesized, could be Chinese, English, Number, etc. 
   */
  void speak(String word);
  
  /**
   * @fn speak
   * @brief Speech synthesis function 
   * @param word Content to be synthesized, could be Chinese, English, Number, etc. 
   */
  void speak(const void *data);
  
  /**
   * @fn speak
   * @brief Speech synthesis function,the data to be converted is put into Flash
   * @param word Content to be synthesized, could be Chinese, English, Number, etc. 
   */
  void speak(const __FlashStringHelper *data);
  
  /**
   * @fn sleep
   * @brief Set sensor to sleep mode 
   */
  void sleep();
  
  /**
   * @fn wakeup
   * @brief Wake up sensor from sleep mode 
   */
  void wakeup();
  
  /**
   * @fn setVolume
   * @brief Set voice volume
   * @param voc  Volume value(0-9)
   */
  void setVolume(uint8_t voc);
  
  /**
   * @fn setSpeed
   * @brief Set playback speed 
   * @param speed Speed value (0-9)
   */
  void setSpeed(uint8_t speed);

  /**
   * @fn setSoundType
   * @brief Set sound type 
   * @param type eMale:Male, eFemale:Female, eDonaldduck: Donaldduck 
   */
  void setSoundType(eSoundType_t type);

  /**
   * @fn setTone
   * @brief Set the tone 
   * @param tone Tone value (0-9)
   */
  void setTone(uint8_t tone);

  /**
   * @fn setEnglishPron
   * @brief Set how to read English 
   * @param pron eAlphabet: letter, eWord: word
   */
  void setEnglishPron(eENpron_t pron);
  
  /**
   * @fn reset
   * @brief Reset settings to default 
   */
  void reset();
  
  /**
   * @fn enableRhythm
   * @brief  The function is only used for Chinese reading
   * @param enable true,false
   */
  void enableRhythm(bool enable);
  
  /**
   * @fn setOnePron
   * @brief Set how to read "1" in phone number 
   * @param pron eYao: read as "yao", eChone: read as "yi"
   */
  void setOnePron(eOnePron_t pron);
  
  /**
   * @fn setNamePron
   * @brief Set whether to use surname reading principle mandatorily 
   * @param pron eName: force, eAutojudgedn: auto judge
   */
  void setNamePron(eNamePron_t pron);
  
  /**
   * @fn setZeroPron
   * @brief set how to read "0" in phone number 
   * @details set the sound of zero
   * @param pron eZreo: read as "zero", eOu: read as "ou"
   */
  void setZeroPron(eZeroPron_t pron);
  
  /**
   * @fn setLanguage
   * @brief  Synthesize Arabic number, unit, special character into Chinese or English 
   * @param style eChinesel: Chinese, eEnglishl: English, eAutojudgel: Auto judge
   */
  void setLanguage(eLanguage_t style);
  
  /**
   * @fn enablePINYIN
   * @brief Enable PinYin Synthesis
   * @details enable pinyin pronunciation
   * @param enable true: enable, false: disable 
   */
  void enablePINYIN(bool enable);
  
  /**
   * @fn setSpeechStyle
   * @brief Set synthesis style 
   * @param style eCaton: word by word, eSmooth: fluently
   */
  void setSpeechStyle(eSpeechStyle_t style);
  
  /**
   * @fn setDigitalPron
   * @brief Set how to read long numbers 
   * @param pron eNumber: phone number, eNumeric: number, eAutojudged: Auto judge
   */
  void setDigitalPron(eDigitalPron_t pron);
  
  /**
   * @fn stopSynthesis
   * @brief Stop synthesis 
   */
  void stopSynthesis();
  
  /**
   * @fn pauseSynthesis
   * @brief Synthesis pause
   */
  void pauseSynthesis();

  /**
   * @fn recoverSynthesis
   * @brief Recover synthesis 
   * @details resumes from paused compositing state
   */
  void recoverSynthesis();
  
  /**
   * @fn wait
   * @brief Wait for speech synthesis to complete 
   */
  void wait();
  
  /**
   * @fn speakElish
   * @brief Synthesize English char string
   * @param word english string
   */
  void speakElish(String word);
  
private:


  uint8_t *_utf8;
  uint8_t *_unicode;
  uint16_t uniLen = 0;
  uint16_t _index=0;
  uint16_t _len=0;
  uint16_t __index = 0;
  eState_t curState = eNone;
  eState_t lastState = eNone;
  bool lanChange = false;
  bool _isFlash = false;
  uint16_t getWordLen();
  virtual uint8_t readACK()= 0;
  void sendPack(uint8_t cmd,uint8_t* data =NULL,uint16_t len = 0);
  sSubMess_t getSubMess(const void *data);
  virtual uint8_t sendCommand(uint8_t *data,uint8_t length)=0;
  virtual uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length)=0;

};


class DFRobot_SpeechSynthesis_I2C :public DFRobot_SpeechSynthesis{
public:
  /**
   * @fn DFRobot_SpeechSynthesis_I2C
   * @brief Constructor 
   * @param pWire I2C BUS pointer object， construct device, can pass parameter or not, default to Wire
   * @param address 7bits I2C address, the first three bits determine the value of the address, default to 0x50
   */
  DFRobot_SpeechSynthesis_I2C(TwoWire *pWire = &Wire, uint8_t address = I2C_ADDR);
  ~DFRobot_SpeechSynthesis_I2C();
  /**
   * @fn begin
   * @brief init function
   */
  void begin();
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
  /**
   * @fn DFRobot_SpeechSynthesis_UART
   * @brief Constructor 
   */
  DFRobot_SpeechSynthesis_UART();
  /**
   * @fn begin
   * @brief init function
   */
  bool begin(Stream &s);

private:
  uint8_t readACK();
  uint8_t sendCommand(uint8_t *data,uint8_t length);
  uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length);
  
  Stream *_s;
  uint32_t _baudRate;
};







#endif
