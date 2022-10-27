# -*- coding: utf-8 -*
'''!
  @file  get_button_status.py
  @brief  Button functon demostration 
  @details  The LED turns on in red when button pressed, and goes off when released 
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
RGBButton = DFRobot_RGBButton(i2c_addr = 0x23, bus = 1)


def setup():
  while not RGBButton.begin() :
    print ('Please check that the device is properly connected!!!')
    time.sleep(3)
  print("RGBButton begin successfully!\n")


def loop():
  global flag
  '''
    # @brief Get module button status 
    # @return Module current button status: 
    # @retval   true - Button pressed 
    # @retval   false - Button not pressed
  '''
  if RGBButton.get_button_status() :
    flag = 1

    '''
      # @brief Set the 7 basic colors and white & black(white and black correspond to led on and off) 
      # @param color - The corresponding values of seven basic colors and white & black: 
      # @n  e_red, e_orange, e_yellow, e_green, e_cyan, e_blue, e_purple, e_white, e_black
    '''
    RGBButton.set_RGB_color(RGBButton.e_red)

    time.sleep(0.05)
  elif 1 == flag  :
    flag = 0
    RGBButton.set_RGB_color(RGBButton.e_black)   # Led turns off when button released. 


if __name__ == "__main__":
  global flag
  flag = 0
  setup()
  while True:
    loop()
