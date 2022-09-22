# -*- coding: utf-8 -*
'''!
  @file  button_cascade.py
  @brief  Button cascade function demonstration
  @details  Cascade 3 button modules via I2C, the 3 modules all show white LEDs by default. When button pressed, they change to red, green, and blue LEDs correspondingly
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2022-05-17
  @url  https://github.com/DFRobot/DFRobot_RGBButton
'''
from __future__ import print_function
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))

from DFRobot_RGBButton import *

'''
  # Instantiate an object to drive our sensor;
  # Set address according to encoder DIP switch
  # (the setting takes effect after encoder power fail and restart):
  # | A2 | A1 | A0 | ADDR |
  # |----|----|----|------|
  # | 0  | 0  | 0  | 0x23 |
  # | 0  | 0  | 1  | 0x24 |
  # | 0  | 1  | 0  | 0x25 |
  # | 0  | 1  | 1  | 0x26 |
  # | 1  | 0  | 0  | 0x27 |
  # | 1  | 0  | 1  | 0x28 |
  # | 1  | 1  | 0  | 0x29 |
  # | 1  | 1  | 1  | 0x2A |
'''
RGBButton1 = DFRobot_RGBButton(i2c_addr = 0x23, bus = 1)
RGBButton2 = DFRobot_RGBButton(i2c_addr = 0x24, bus = 1)
RGBButton3 = DFRobot_RGBButton(i2c_addr = 0x25, bus = 1)


def setup():
  while not RGBButton1.begin() :
    print ('Please check that the device is properly connected!!!')
    time.sleep(3)
  while not RGBButton2.begin() :
    print ('Please check that the device is properly connected!!!')
    time.sleep(3)
  while not RGBButton3.begin() :
    print ('Please check that the device is properly connected!!!')
    time.sleep(3)
  print("RGBButton begin successfully!\n")

  '''
    # @brief Set the basic seven colors, and white & black (white and black correspond to LED on and off respectively)
    # @param color - The corresponding values of the basic seven colors and white & black: 
    # @n  e_red, e_orange, e_yellow, e_green, e_cyan, e_blue, e_purple, e_white, e_black
  '''
  RGBButton1.set_RGB_color(RGBButton1.e_white)
  RGBButton2.set_RGB_color(RGBButton2.e_white)
  RGBButton3.set_RGB_color(RGBButton3.e_white)


def loop():
  global flag1, flag2, flag3
  '''
    # @brief Get button status
    # @return The current button status:
    # @retval   true - the button is pressed
    # @retval   false - the button is not pressed
  '''
  if RGBButton1.get_button_status() :   # button 1, show red LED when pressed
    flag1 = 1
    RGBButton1.set_RGB_color(RGBButton1.e_red)
    time.sleep(0.05)
  elif 1 == flag1  :
    flag1 = 0
    RGBButton1.set_RGB_color(RGBButton1.e_white)

  if RGBButton2.get_button_status() :   # button 2, show green LED when pressed
    flag2 = 1
    RGBButton2.set_RGB_color(RGBButton2.e_green)
    time.sleep(0.05)
  elif 1 == flag2  :
    flag2 = 0
    RGBButton2.set_RGB_color(RGBButton2.e_white)

  if RGBButton3.get_button_status() :   # button 3, show blue LED when pressed
    flag3 = 1
    RGBButton3.set_RGB_color(RGBButton3.e_blue)
    time.sleep(0.05)
  elif 1 == flag3  :
    flag3 = 0
    RGBButton3.set_RGB_color(RGBButton3.e_white)


if __name__ == "__main__":
  global flag1, flag2, flag3
  flag1, flag2, flag3 = 0, 0, 0
  setup()
  while True:
    loop()
