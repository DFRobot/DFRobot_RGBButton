# DFRobot_RGBButton
* [English Version](./README.md)

RGB 按钮模块，一个带有rgb灯的漂亮彩色按钮。可以通过i2c设置RGB灯颜色和读取其按键状态，也可以直接通过中断引脚获取按键状态，地址拨码开关的存在，使得多个按钮可以级联。

![产品实物图](./resources/images/RGBButton.png)


## 产品链接 (https://www.dfrobot.com.cn/)
    SKU: DFR0991


## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述

* 系统自定义七种颜色，红橙黄绿青蓝紫；用户也可用rgb值自定义颜色
* 用户可根据配置PWM信号控制RGB灯的亮度，独立配置周期和脉宽
* I2C地址可根据拨码开关来设置
* 按键具有中断通知功能，正常状态为低电平，按键按下为高电平


## 库安装

这里有2种安装方法：

1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_RGBButton 库。


## 方法

```C++

  /**
   * @fn DFRobot_RGBButton
   * @brief 构造函数
   * @param pWire - Wire对象是在Wire.h中定义的，所以只要使用&Wire，就可以指向和使用Wire中的方法
   * @param i2cAddr - RGB 按钮的 I2C 地址
   * @return None
   */
  DFRobot_RGBButton(TwoWire *pWire=&Wire, uint8_t i2cAddr=RGBBUTTON_DEFAULT_I2C_ADDR);

  /**
   * @fn begin
   * @brief 初始化函数
   * @return Bool类型，成功时为true，错误时为false
   */
  bool begin(void);

  /**
   * @fn setRGBColor
   * @brief 设置七种基础颜色以及白黑(白黑对应亮灭)或者用RGB值设置对应颜色
   * @param color - 七种基础颜色以及白黑对应的值: 
   * @n  eRed, eOrange, eYellow, eGreen, eCyan, eBlue, ePurple, eWhite, eBlack
   * @param r - 红灯的脉宽值
   * @param g - 绿灯的脉宽值
   * @param b - 蓝灯的脉宽值
   * @return None
   */
  void setRGBColor(eGeneralRGBValue_t color);
  void setRGBColor(uint8_t r, uint8_t g, uint8_t b);

  /**
   * @fn getButtonStatus
   * @brief 获取模块按键状态
   * @return 模块当前的按键状态:
   * @retval   true - 按键按下
   * @retval   false - 按键未按下
   */
  bool getButtonStatus(void);

```


## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## 历史

- 2022/05/17 - 1.0.0 版本


## 创作者

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

