# DFRobot_RGBButton
* [中文版](./README_CN.md)

This RGB LED button module can be set to different colors via I2C. And the button status can be obtained via either I2C or the interrupt pin. The address DIP switch allows cascading multiple buttons.

![产品实物图](./resources/images/RGBButton.png)


## Product Link (https://www.dfrobot.com/)
    SKU: DFR0991


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* There are seven system-defined colors, red, orange, yellow, green, indigo, blue, and purple; users can also customize the color by changing RGB values
* Users can control the brightness of RGB LEDs by configuring PWM signal, the period and pulse width are configured independently
* I2C address can be set by the DIP switch
* The button can indicate interrupt status, low level when button released, high level when button pressed


## Installation

There two methods:

1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_RGBButton library from the Arduino Software Library Manager and download it.


## Methods

```C++

  /**
   * @fn DFRobot_RGBButton
   * @brief Constructor
   * @param pWire - Wire object is defined in Wire.h, so just use &Wire and the methods in Wire can be pointed to and used
   * @param i2cAddr - RGBButton I2C address.
   * @return None
   */
  DFRobot_RGBButton(TwoWire *pWire=&Wire, uint8_t i2cAddr=RGBBUTTON_DEFAULT_I2C_ADDR);

  /**
   * @fn begin
   * @brief Init function
   * @return bool type, true if successful, false if error
   */
  bool begin(void);

  /**
   * @fn setRGBColor
   * @brief Set the seven basic colors, and white & black (white and black correspond to on and off respectively) or set the corresponding color with RGB values
   * @param color - the corresponding values of the seven basic colors and white & black: 
   * @n  eRed, eOrange, eYellow, eGreen, eCyan, eBlue, ePurple, eWhite, eBlack
   * @param r - pulse width value for red LED
   * @param g - pulse width of green LED
   * @param b - pulse width of blue LED
   * @return None
   */
  void setRGBColor(eGeneralRGBValue_t color);
  void setRGBColor(uint8_t r, uint8_t g, uint8_t b);

  /**
   * @fn getButtonStatus
   * @brief Get button status
   * @return The current button status:
   * @retval   true - the button is pressed
   * @retval   false - the button is not pressed
   */
  bool getButtonStatus(void);

```


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## History

- 2022/05/17 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

