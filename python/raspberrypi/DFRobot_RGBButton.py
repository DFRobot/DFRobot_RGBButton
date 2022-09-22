# -*- coding: utf-8 -*
'''!
  @file  DFRobot_RGBButton.py
  @brief  Define infrastructure of DFRobot_RGBButton class
  @details  
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2022-05-17
  @url  https://github.com/DFRobot/DFRobot_RGBButton
'''
import sys
import time

import smbus

import logging
from ctypes import *


logger = logging.getLogger()
# logger.setLevel(logging.INFO)   # Display all print information
logger.setLevel(logging.FATAL)   # If you don’t want to display too many prints, only print errors, please use this option
ph = logging.StreamHandler()
formatter = logging.Formatter("%(asctime)s - [%(filename)s %(funcName)s]:%(lineno)d - %(levelname)s: %(message)s")
ph.setFormatter(formatter) 
logger.addHandler(ph)


## rgbbutton default i2c addr
RGBBUTTON_DEFAULT_I2C_ADDR  = 0x2A
## RGBButton chip ID
RGBBUTTON_PART_ID           = 0x43DF

# RGBButton register address
## RGBButton I2C ADDR REG
RGBBUTTON_I2C_ADDR_REG      = 0x00

## RGBButton RED REG
RGBBUTTON_RED_REG           = 0x01
## RGBButton GREEN REG
RGBBUTTON_GREEN_REG         = 0x02
## RGBButton BLUE REG
RGBBUTTON_BLUE_REG          = 0x03

## RGBBUTTON BUTTON SIGNAL REG
RGBBUTTON_BUTTON_SIGNAL_REG = 0x04

## RGBButton PID MSB REG
RGBBUTTON_PID_MSB_REG       = 0x09
## RGBButton PID LSB REG
RGBBUTTON_PID_LSB_REG       = 0x0A


class DFRobot_RGBButton(object):
    '''!
      @brief Define DFRobot_RGBButton basic class
      @details Drive the gas sensor
    '''

    e_red    = 0xFF0000   ## 红色
    e_orange = 0xFF7F00   ## 橙色
    e_yellow = 0xFFFF00   ## 黄色
    e_green  = 0x00FF00   ## 绿色
    e_cyan   = 0x00FFFF   ## 青色
    e_blue   = 0x0000FF   ## 蓝色
    e_purple = 0x8B00FF   ## 紫色
    e_white  = 0xFFFFFF   ## 白色(相当于亮灯)
    e_black  = 0x000000   ## 黑色(相当于灭灯)

    def __init__(self, i2c_addr=RGBBUTTON_DEFAULT_I2C_ADDR, bus=1):
        '''!
          @brief Module init
        '''
        self._addr = i2c_addr
        self._i2c = smbus.SMBus(bus)

    def begin(self):
        '''!
          @brief Initialize sensor
          @return  Return init status
          @retval True indicate initialization succeed
          @retval False indicate initialization failed
        '''
        ret = True
        chip_id = self._read_reg(RGBBUTTON_PID_MSB_REG, 2)
        logger.info( ((chip_id[0] << 8) | chip_id[1]) )
        if RGBBUTTON_PART_ID != ((chip_id[0] << 8) | chip_id[1]):
            ret = False
        return ret

    def set_RGB_color(self, *args):
        '''!
          @brief 设置七种基础颜色以及白黑(白黑对应亮灭) 或 用RGB值设置对应颜色
          @param color - 七种基础颜色以及白黑对应的值: 
          @n  e_red, e_orange, e_yellow, e_green, e_cyan, e_blue, e_purple, e_white, e_black
          @param r - 红灯的脉宽值
          @param g - 绿灯的脉宽值
          @param b - 蓝灯的脉宽值
        '''
        rgb_buf = [0] * 3
        if 1 == len(args):
          rgb_buf[0] = (args[0] >> 16) & 0xFF
          rgb_buf[1] = (args[0] >> 8) & 0xFF
          rgb_buf[2] = args[0] & 0xFF
        elif 3 == len(args):
          rgb_buf[0] = args[0]
          rgb_buf[1] = args[1]
          rgb_buf[2] = args[2]
        self._write_reg(RGBBUTTON_RED_REG, rgb_buf)

    def get_button_status(self):
        '''!
          @brief 获取模块按键状态
          @return 模块当前的按键状态:
          @retval   true - 按键按下
          @retval   false - 按键未按下
        '''
        button_status = False
        if 1 == self._read_reg(RGBBUTTON_BUTTON_SIGNAL_REG, 1)[0] :
          button_status = True
        return button_status

    def _write_reg(self, reg, data):
        '''!
          @brief writes data to a register
          @param reg register address
          @param data written data
        '''
        if isinstance(data, int):
            data = [data]
            #logger.info(data)
        try:
          self._i2c.write_i2c_block_data(self._addr, reg, data)
        except IOError:
          print("[Errno 121] Remote I/O error")

    def _read_reg(self, reg, length):
        '''!
          @brief read the data from the register
          @param reg register address
          @param length read data length
          @return read data list
        '''
        try:
          return self._i2c.read_i2c_block_data(self._addr, reg, length)
        except IOError:
          print("[Errno 121] Remote I/O error")
          return [0] * length
