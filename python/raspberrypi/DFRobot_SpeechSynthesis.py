# coding=gbk
  
""" 
  @file DFRobot_SpeechSynthesis.py
  @note DFRobot_SpeechSynthesis Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [fengli](li.feng@dfrobot.com)
  version  V1.0
  date  2020-11-04
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_SpeechSynthesis
"""
import serial
import time
import smbus
import array
import numpy as np
from sys import version_info
I2C_ADDR               = 0x40  #
INQUIRYSTATUS          = 0x21  #
ENTERSAVEELETRI        = 0x88  #
WAKEUP                 = 0xFF  #

START_SYNTHESIS        = 0x01  #
START_SYNTHESIS1       = 0x05  #
STOP_SYNTHESIS         = 0x02  #
PAUSE_SYNTHESIS        = 0x03  #
RECOVER_SYNTHESIS      = 0x04  #
I2C_MODE                  = 0x01  
UART_MODE                 = 0x02

MEAL                  = 0x04
FEMEAL                = 0x03
DONALDDUCK            = 0x05
ALPHABET              = 0X06
WORD                  = 0X07


CHINESE               = 0XA0
ENGLISH               = 0XA1
NONE                  = 0XA2
CATON                 = 0XA3
SMOOTH                = 0XA4
PINYIN_ENABLE         = 0XA5
PINYIN_DISABLE        = 0XA6
CHINESEL              = 0XA7
ENGLISHL              = 0XA8
AUTOJUDGEL            = 0XA9
NUMBER                = 0XAA
NUMERIC               = 0XAB
AUTOJUDGED            = 0XAC
ZREO                  = 0XAD
OU                    = 0XAE
YAO                   = 0XAF
CHONE                 = 0XB0
NAME                  = 0XB1
AUTOJUDGEDN           = 0XB2
ERROR                     = -1
  
class DFRobot_SpeechSynthesis(object):

  __txbuf        = [0]          # i2c send buffer
  __alcoholdata  = [0]*101      # alcohol data
  __uart_i2c     =  0
  def __init__(self ,bus ,Baud):
    if bus != 0:
      self.i2cbus = smbus.SMBus(bus)
      self.__uart_i2c = I2C_MODE;
    else:
      self.ser = serial.Serial("/dev/ttyAMA0" ,baudrate=Baud,stopbits=1, timeout=0.5)
      self.__uart_i2c = UART_MODE;
      if self.ser.isOpen == False:
        self.ser.open()

  def speak(self ,string):
      str = string.encode('gb2312')
      head = [0xfd,0x00,0x00,0x01,0x00]
      if version_info.major == 2 and version_info.minor == 7:
         data = array.array('B', str)
      else:
         data = list(str)
      data2 = (list(data))
      lenght = len(data2) + 2
      head[1] = lenght>> 8
      head[2] = lenght & 0xff
      data1 = head +data2
      self.read_ack(1)
      self.read_ack(1)
      self.write_cmd(data1)
      self.wait()
      return
  '''
    @brief Wait for speech synthesis to complete 
  '''
  def wait(self):
      while 1:
        result =self.read_ack(1)
        if(result == 0x41):
          break
      while 1:
        result =self.read_ack(1)
        if(result == 0x4f):
          break
  '''
    @brief Set voice volume 
    @param voc, Volume value(0-9)
  '''
  def setVoice(self, voc):
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,118,49,93]
      if(voc > 9 or voc < 0):
         return
      list1[7]= voc + 48
      self.write_cmd(list1)
  '''
    @brief Set playback speed 
    @param speed, Speed(0-9)
  '''
  def setSpeed(self, speed):
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,115,54,93]

      if(speed > 9 or speed < 0):
         return
      list1[7]= speed + 48
      self.write_cmd(list1)
  '''
    @brief Set voice type 
    @param type(MALE:male, FEMALE:famale, DONALDDUCK:Donaldduck)
  '''
  def setSoundType(self, type):
      if(type == MEAL):
        self.speak("[m51]")
      elif(type == FEMEAL):
        self.speak("[m3]")
      elif(type == DONALDDUCK):
        self.speak("[m54]")
      else:
        print("no that type")
  '''
    @brief Set tone 
    @param tone, Tone(0-9)
  '''
  def setTone(self, tone):
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,116,54,93]
      if(tone > 9 or tone < 0):
         return
      list1[7]= tone + 48
      self.write_cmd(list1)
  '''
    @brief Set how to read English 
    @param pron(ALPHABET: letter, WORD: word)
  '''
  def setEnglishPron(self, pron):  
     if(pron == ALPHABET):
       self.speak("[h1]")
     elif(pron == WORD):
       self.speak("[h2]")
  '''
     @brief This function is only used for reading Chinese
     @param enable(true;alse)
  '''
  def enableRhythm(self,enable):
     if(enable == True):
        str1="[z1]"
     elif(enable ==False):
        str1="[z0]"
     self.speak(str1)
  '''
     @brief Set how to read long numbers 
     @param pron(NUMBER: phone number, NUMERIC: number, AUTOJUDGED: auto judge)
  '''
  def setDigitalPron(self,pron):
     if(pron == NUMBER):
        str1="[n1]"
     elif(pron ==NUMERIC):
        str1="[n2]"
     elif(pron == AUTOJUDGED):
        str1="[n0]"
     self.speak(str1)
  '''
     @brief Enable PinYin synthesis 
     @param enable(true: enable, false:disable)
  '''
  def enablePINYIN(self,enable):
     if(enable == True):
        str1="[i1]"
     elif(enable ==False):
        str1="[i0]"
     self.speak(str1)
  '''
     @brief Set synthesis style 
     @param enable(CATON: word by word; SMOOTH: fluently)
  '''
  def setSpeechStyle(self,style):
     if(style == CATON):
       str1="[f0]"
     elif(style ==SMOOTH):
       str1="[f1]"
     self.speak(str1)
  '''
     @brief Synthesize Arabic number, unit, special characters into Chinese or English 
     @param style(CHINESEL:Chinese, ENGLISHL: English, AUTOJUDGEL: Auto judge)
  '''
  def setLanguage(self,style):
    if(style == CHINESEL):
       str1="[g1]"
    elif(style ==ENGLISHL):
       str1="[g2]"
    elif(style == AUTOJUDGEL):
       str1="[g0]"
    self.speak(str1)
  '''
     @brief Set how to read "0" in phone number 
     @param pron(ZREO: read as "zero"; OU: read as "ou")
  '''
  def setZeroPron(self,pron):
     if(pron == ZREO):
        str1="[o0]"
     elif(pron ==OU):
        str1="[o1]"
     self.speak(str1)
  '''
    @brief Set how to read "1" in phone number 
    @param pron(YAO: read as "yao"; CHONE: read as "yi")
  '''
  def setOnePron(self,pron):
     if(pron == YAO):
        str1="[y0]"
     elif(pron ==CHONE):
        str1="[y1]"
     self.speak(str1)
  '''
     @brief Set whether to use surname reading principle mandatorily 
     @param pron(NAME: mandatory; AUTOJUDGEDN: auto judge)
  '''
  def setNamePron(self,pron):
     if(pron == NAME):
        str1="[r1]"
     elif(pron ==AUTOJUDGEDN):
        str1="[r0]"
     self.speak(str1)
  '''
     @brief Test function 
  '''
  def test(self ):
    data = [0xfd,0x00,0x0C,0x01,0x00,66,67,68,69,70,71,72,73,74,75]
    self.write_cmd(data)
  '''
    @brief Reset settings to default
  '''
  def reset(self):
    speakElish("[d]");
'''
  @brief An example of an i2c interface module
'''
class DFRobot_SpeechSynthesis_I2C(DFRobot_SpeechSynthesis): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    #print(self.__addr)
    super(DFRobot_SpeechSynthesis_I2C, self).__init__(bus,0)

  '''
    @brief writes data to a register
    @param data written data
  '''
  def write_cmd(self, data):
        self.i2cbus.write_block_data(self.__addr,0x1,data)
        #print(data)

  '''
    @brief read the data from the register
  '''
  def read_ack(self ,len):
    try:
      rslt = self.i2cbus.read_byte(self.__addr)
    except:
      rslt = -1
    return rslt

class DFRobot_SpeechSynthesis_UART(DFRobot_SpeechSynthesis): 

  def __init__(self ,Baud):
    self.__Baud = Baud;
    super(DFRobot_SpeechSynthesis_UART, self).__init__(0,Baud)

  '''
    @brief writes data to a register
    @param data written data
  '''
  def write_cmd(self,data):
      self.ser.write(data)
      return
  '''
    @brief read the data from the register
  '''
  def read_ack(self,len):
    #timenow = time.time()
    #recv = 0
    #i = 0
    #count = self.ser.inWaiting()
    a = [0]
    a[0] = self.ser.read(1)
    #print(a[0])
    if(a[0] == b'A'):
       return 0x41
    if(a[0] == b'O'):
       return 0x4f
    #self.ser.flushInput()
    return a[0]
