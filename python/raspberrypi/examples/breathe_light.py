# -*- coding: utf-8 -*
'''!
  @file  breathe_light.py
  @brief  Breathing lights function demonstration
  @details  The button RGB LED presents a colorful breathing light effect, and turns red when the button is pressed.
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

from math import sin
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
  global t, r_value, g_value, b_value
  '''
    # @brief Get button status
    # @return The current button status:
    # @retval   true - the button is pressed
    # @retval   false - the button is not pressed
  '''
  if RGBButton.get_button_status() :
    '''
      # @brief Set the basic seven colors, and white & black (white and black correspond to LED on and off respectively)
      # @param color - The corresponding values of the basic seven colors and white & black: 
      # @n  e_red, e_orange, e_yellow, e_green, e_cyan, e_blue, e_purple, e_white, e_black
    '''
    RGBButton.set_RGB_color(RGBButton.e_red)
    time.sleep(0.1)
  else :
    r_value = int((abs(sin(3.14 * t / 180))) * 255)
    g_value = int((abs(sin(3.14 * (t + 60) / 180))) * 255)
    b_value = int((abs(sin(3.14 * (t + 120) / 180))) * 255)
    t += 1

    '''
      # @brief Set the corresponding colors by setting RGB values
      # @param r - pulse width value of red LED
      # @param g - pulse width value of green LED
      # @param b - pulse width value of blue LED
    '''
    RGBButton.set_RGB_color(r=r_value, g=g_value, b=b_value)

    time.sleep(0.1)


if __name__ == "__main__":
  global t, r_value, g_value, b_value
  t = 0   # Basic transformations of RGB values
  r_value, g_value, b_value = 0, 0, 0
  setup()
  while True:
    loop()
