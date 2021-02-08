## DFRobot Speech Synthesis Module



## DFRobot Speech Synthesis Module Library for RaspberryPi

Provide the Raspberry Pi library for the DFRobot_Speech Synthesis module.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)

## Summary

   1.Speech Synthesis <br>

## Feature

  1. <br>
  2. <br>

## Installation

This Sensor should work with DFRobot_SpeechSynthesis on RaspberryPi. <br>
Run the program:

```
$> python get_alcohol_data.py
```

## Methods

```py

  def speak(self ,string):
    '''
      @brief Speech Synthesis
      @param string: Content to be synthesized, could be Chinese, English, number, etc. 
    '''

  def setVoice(self, voc):
    '''
      @brief Set voice volume 
      @param voc: Volume(0-9)
    '''
  def setSpeed(self, speed):
    '''
      @brief Set playback speed 
      @param speed: Speed (0-9)
    '''
  def setSoundType(self, type):
    '''
      @brief Set voice type 
      @param type:(MALE:male, FEMALE:female, DONALDDUCK: DonaldDuck)
    '''
  def setTone(self, tone):
    '''
      @brief Set tone 
      @param tone: Tone(0-9)
    '''
  def setEnglishPron(self, pron): 
    '''
      @brief Set how to read English 
      @param pron:(ALPHABET: letter, WORD: word)
    '''
```
## History

- Data 2020-11-6
- Version V1.0


## Credits

Written by fengli(li.feng@dfrobot.com), 2020.11.6 (Welcome to our [website](https://www.dfrobot.com/))
