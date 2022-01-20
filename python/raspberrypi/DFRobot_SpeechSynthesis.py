# coding=gbk
""" 
  @file DFRobot_SpeechSynthesis.py
  @brief DFRobot_SpeechSynthesis Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date        2020-10-9
  @url https://github.com/DFRobot/DFRobot_SpeechSynthesis
"""
import serial
import time
import smbus
import array
import numpy as np
from sys import version_info
I2C_ADDR               = 0x40  #i2c address
INQUIRYSTATUS          = 0x21  #Check status
ENTERSAVEELETRI        = 0x88  #
WAKEUP                 = 0xFF  #Wake-up command

START_SYNTHESIS        = 0x01  #start synthesis command 0
START_SYNTHESIS1       = 0x05  #Start synthesis command 1
STOP_SYNTHESIS         = 0x02  #End speech synthesis
PAUSE_SYNTHESIS        = 0x03  #pause speech synthesis command
RECOVER_SYNTHESIS      = 0x04  #Resume speech synthesis commands
I2C_MODE                  = 0x01  
UART_MODE                 = 0x02

MEAL                  = 0x04   #Male voice
FEMEAL                = 0x03   #female voice
DONALDDUCK            = 0x05   #Voice of Donald Duck

ALPHABET              = 0X06   #Spell
WORD                  = 0X07   #word


CHINESE               = 0XA0   #Chinese
ENGLISH               = 0XA1   #English
NONE                  = 0XA2   #
CATON                 = 0XA3   #Word by word
SMOOTH                = 0XA4   #Fluently
PINYIN_ENABLE         = 0XA5   #Use Pinyin to read
PINYIN_DISABLE        = 0XA6   #don't use pinyin pronunciation
CHINESEL              = 0XA7   #
ENGLISHL              = 0XA8   #
AUTOJUDGEL            = 0XA9   #Auto Judge
NUMBER                = 0XAA   #Telephone number
NUMERIC               = 0XAB   #
AUTOJUDGED            = 0XAC   #Auto Judge
ZREO                  = 0XAD   #Read as 'zero'
OU                    = 0XAE   #Read as'ou'
YAO                   = 0XAF   #Read as 'yao'
CHONE                 = 0XB0   #Read as 'yi'
NAME                  = 0XB1   #
AUTOJUDGEDN           = 0XB2   #
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
      '''！
        @fn speak
        @brief Speech synthesis function 
        @param string word Content to be synthesized, could be Chinese, English, Number, etc. 
      '''
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

  def wait(self):
      '''！
        @brief Wait for speech synthesis to complete 
      '''
      while 1:
        result =self.read_ack(1)
        if(result == 0x41):
          break
      while 1:
        result =self.read_ack(1)
        if(result == 0x4f):
          break

  def set_voice(self, voc):
      '''！
        @brief Set voice volume 
        @param voc Volume value(0-9)
      '''
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,118,49,93]
      if(voc > 9 or voc < 0):
         return
      list1[7]= voc + 48
      self.write_cmd(list1)

  def set_speed(self, speed):
      '''！
        @brief Set playback speed 
        @param speed  Speed(0-9)
      '''
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,115,54,93]

      if(speed > 9 or speed < 0):
         return
      list1[7]= speed + 48
      self.write_cmd(list1)

  def set_soundType(self, type):
      '''！
        @brief Set voice type 
        @param type(MALE:male, FEMALE:famale, DONALDDUCK:Donaldduck)
      '''
      if(type == MEAL):
        self.speak("[m51]")
      elif(type == FEMEAL):
        self.speak("[m3]")
      elif(type == DONALDDUCK):
        self.speak("[m54]")
      else:
        print("no that type")

  def set_tone(self, tone):
      '''！
        @brief Set tone 
        @param tone Tone(0-9)
      '''
      list1 = [0xfd,0x00,0x06,0x01,0x00,91,116,54,93]
      if(tone > 9 or tone < 0):
         return
      list1[7]= tone + 48
      self.write_cmd(list1)

  def set_english_pron(self, pron):  
     '''！
       @brief Set how to read English 
       @param pron(ALPHABET: letter, WORD: word)
     '''
     if(pron == ALPHABET):
       self.speak("[h1]")
     elif(pron == WORD):
       self.speak("[h2]")

  def enable_rhythm(self,enable):
     '''！
        @brief This function is only used for reading Chinese
        @param enable(true;alse)
     '''
     if(enable == True):
        str1="[z1]"
     elif(enable ==False):
        str1="[z0]"
     self.speak(str1)

  def set_digitalPron(self,pron):
     '''！
        @brief Set how to read long numbers 
        @param pron(NUMBER: phone number, NUMERIC: number, AUTOJUDGED: auto judge)
     '''
     if(pron == NUMBER):
        str1="[n1]"
     elif(pron ==NUMERIC):
        str1="[n2]"
     elif(pron == AUTOJUDGED):
        str1="[n0]"
     self.speak(str1)

  def enable_PINYIN(self,enable):
     '''！
        @brief Enable PinYin synthesis 
        @param enable(true: enable, false:disable)
     '''
     if(enable == True):
        str1="[i1]"
     elif(enable ==False):
        str1="[i0]"
     self.speak(str1)

  def set_speech_style(self,style):
     '''！
        @brief Set synthesis style 
        @param enable(CATON: word by word; SMOOTH: fluently)
     '''
     if(style == CATON):
       str1="[f0]"
     elif(style ==SMOOTH):
       str1="[f1]"
     self.speak(str1)

  def set_language(self,style):
    '''！
       @brief Synthesize Arabic number, unit, special characters into Chinese or English 
       @param style(CHINESEL:Chinese, ENGLISHL: English, AUTOJUDGEL: Auto judge)
    '''
    if(style == CHINESEL):
       str1="[g1]"
    elif(style ==ENGLISHL):
       str1="[g2]"
    elif(style == AUTOJUDGEL):
       str1="[g0]"
    self.speak(str1)

  def set_zero_pron(self,pron):
     '''！
        @brief Set how to read "0" in phone number 
        @param pron(ZREO: read as "zero"; OU: read as "ou")
     '''
     if(pron == ZREO):
        str1="[o0]"
     elif(pron ==OU):
        str1="[o1]"
     self.speak(str1)

  def set_one_pron(self,pron):
     '''！
       @brief Set how to read "1" in phone number 
       @param pron(YAO: read as "yao"; CHONE: read as "yi")
     '''
     if(pron == YAO):
        str1="[y0]"
     elif(pron ==CHONE):
        str1="[y1]"
     self.speak(str1)

  def set_name_pron(self,pron):
     '''！
        @brief Set whether to use surname reading principle mandatorily 
        @param pron(NAME: mandatory; AUTOJUDGEDN: auto judge)
     '''
     if(pron == NAME):
        str1="[r1]"
     elif(pron ==AUTOJUDGEDN):
        str1="[r0]"
     self.speak(str1)

  def test(self ):
    '''！
       @brief Test function 
    '''
    data = [0xfd,0x00,0x0C,0x01,0x00,66,67,68,69,70,71,72,73,74,75]
    self.write_cmd(data)

  def reset(self):
    '''！
      @brief Reset settings to default
    '''
    speakElish("[d]");

class DFRobot_SpeechSynthesis_I2C(DFRobot_SpeechSynthesis): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    #print(self.__addr)
    super(DFRobot_SpeechSynthesis_I2C, self).__init__(bus,0)


  def write_cmd(self, data):
    '''！
      @brief writes data to a register
      @param data written data
    '''
    self.i2cbus.write_block_data(self.__addr,0x1,data)
    #print(data)

  def read_ack(self ,len):
    '''！
      @brief read the data from the register
    '''
    try:
      rslt = self.i2cbus.read_byte(self.__addr)
    except:
      rslt = -1
    return rslt

class DFRobot_SpeechSynthesis_UART(DFRobot_SpeechSynthesis): 

  def __init__(self ,Baud):
    self.__Baud = Baud;
    super(DFRobot_SpeechSynthesis_UART, self).__init__(0,Baud)

  def write_cmd(self,data):
    '''！
      @brief writes data to a register
      @param data written data
    '''
    self.ser.write(data)
    return

  def read_ack(self,len):
    '''！
      @brief read the data from the register
    '''
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
