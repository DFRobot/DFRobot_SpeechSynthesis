# coding=gbk

""" 
  @file speechSynthesis.py
  @brief speech synthesis
  @n note: it takes time to stable alcohol concentration, about 1 minutes.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
  version  V1.0
  date  2020-09-09
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_SpeechSynthesis
"""
import sys
sys.path.append("../..")
from DFRobot_SpeechSynthesis import *
from sys import version_info
if version_info.major == 2 and version_info.minor == 7:
   reload(sys)  
   sys.setdefaultencoding('gbk') 
COLLECT_NUMBER   = 1               # collect number, the collection range is 1-100
I2C_MODE         = 0x01            # default use I2C1 

alcohol = DFRobot_SpeechSynthesis_I2C (I2C_MODE ,I2C_ADDR)
#alcohol = DFRobot_SpeechSynthesis_UART(115200)
alcohol.setVoice(9)#Set volume(0-9)
alcohol.setSpeed(5)#Set playback speed (0-9)
alcohol.setSoundType(FEMEAL)#Set voice type/FEMEAL/MEAL/DONALDDUCK
alcohol.setTone(5)#Set tone(0-9)
alcohol.setEnglishPron(WORD)#Set word synthesis mode /WORD/ALPHABET
while True:
  alcohol.speak("i have a book")
  alcohol.speak("She sells seashells by the seashore")
  alcohol.speak("Hello world")
  time.sleep(1)
