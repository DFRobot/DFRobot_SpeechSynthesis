# DFRobot_SpeechSynthesis

Would you like to add voice to your projects? Connect up this Speech Synthesis module, add few couples of lines of code, then here goes, your project starts speaking. Both Chinese and English are "so easy" for this speech synthesis module. It also can broadcast the current time and environment data. Combining with a speech recognition module, you can easily have conversations with your projects! The module uses I2C and UART two communication modes, gravity interface, and is compatible with most main-controllers on the market. Besides, the module already comes with a speaker, so you don't need to buy one.
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

   1. Speech Synthesis <br>


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    
 /**
   *  @brief Speech Synthesis function 
   *  @param word Content to be synthesized, it can be Chinese, English, number, etc. 
   */
  void speak(String word);
  
  /**
   *  @brief Speech synthesis function,the data to be converted is put into Flash
   *  @param word Content to be synthesized, could be Chinese, English, Number, etc. 
  */
  void speak(const __FlashStringHelper *data);
  /**
   *  @brief Set voice volume 
   *  @param voc, Volume value(0-9)
   */
  void setVolume(uint8_t voc);

  /**
   *  @brief Set playback speed 
   *  @param speed, speed value (0-9)
   */
  void setSpeed(uint8_t speed);

  /**
   *  @brief Set voice type 
   *  @param FEMALE1,<Female 1, recommended>
   *         MALE1,<Male 1, recommended>
   *         MALE2,<Male 2>
   *         FEMALE2,<Female 2>
   *         DONALDDUCK,<Donald Duck>
   *         FEMALE3,<Female 3>
   */
  void setSoundType(eSoundType_t type);

  /**
   *  @brief Set the tone 
   *  @param tone, tone value(0-9)
   */
  void setTone(uint8_t tone);

  /**
   *  @brief Set English Pronounce mode 
   *  @param pron(ALPHABET: letter, WORD: word)
   */
  void setEnglishPron(eENpron_t pron);

  /**
   *  @brief Reset setting to default 
   */
  void reset();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- Data 2020-11-6
- Version V1.0


## Credits

Written by fengli(li.feng@dfrobot.com), 2020.11.6 (Welcome to our [website](https://www.dfrobot.com/))





