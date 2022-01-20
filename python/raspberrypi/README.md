## DFRobot_SpeechSynthesis Module

- [中文版](./README_CN.md)

Would you like to add voice to your projects? Connect up this Speech Synthesis module, add few couples of lines of code, then here goes, your project starts speaking. Both Chinese and English are "so easy" for this speech synthesis module. It also can broadcast the current time and environment data. Combining with a speech recognition module, you can easily have conversations with your projects! The module uses I2C and UART two communication modes, gravity interface, and is compatible with most main-controllers on the market. Besides, the module already comes with a speaker, so you don't need to buy one.


![正反面svg效果图](../../resources/images/dfr0760.png)

## Product Link（https://www.dfrobot.com/product-2234.html）

  DFR0760:Speech Synthesis Module(Support English and Chinese)

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)  
* [History](#history)
* [Credits](#credits)

## Summary

   1.Speech Synthesis <br>

## Installation

This Sensor should work with DFRobot_SpeechSynthesis on RaspberryPi. <br>
Run the program:

```python
speech_synthesis.py
```

## Methods

```python

  def speak(self ,string):
    '''！
      @brief Speech Synthesis
      @param string Content to be synthesized, could be Chinese, English, number, etc. 
    '''

  def set_voice(self, voc):
    '''！
      @brief Set voice volume 
      @param voc  Volume(0-9)
    '''
  def set_speed(self, speed):
    '''！
      @brief Set playback speed 
      @param speed  Speed (0-9)
    '''
  def set_sound_type(self, type):
    '''！
      @brief Set voice type 
      @param type (MALE:male, FEMALE:female, DONALDDUCK: DonaldDuck)
    '''
  def set_tone(self, tone):
    '''！
      @brief Set tone 
      @param tone  Tone(0-9)
    '''
  def set_english_pron(self, pron): 
    '''！
      @brief Set how to read English 
      @param pron (ALPHABET: letter, WORD: word)
    '''
```

## compatibility  

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## History

- 2020/11/06 - Version 1.0.0 released.
## Credits

Written by fengli(li.feng@dfrobot.com), 2020.11.6 (Welcome to our [website](https://www.dfrobot.com/))
