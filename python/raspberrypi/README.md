# DFRobot_RGBButton
* [中文版](./README_CN.md)

This RGB LED button module can be set to different colors via I2C. And the button status can be obtained via either I2C or the interrupt pin. The address DIP switch allows cascading multiple buttons.

![产品实物图](../../resources/images/RGBButton.png)


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

To use the library, first download the library file, paste it into the directory you specified, then open the Examples folder and run the demo in that folder.


## Methods

```python

    '''!
      @brief Initialize sensor
      @return  Return init status
      @retval True indicate initialization succeed
      @retval False indicate initialization failed
    '''
    def begin(self):

    '''!
      @brief Set the seven basic colors, and white & black (white and black correspond to on and off respectively) or set the corresponding color with RGB values
      @param color -the corresponding values of the seven basic colors and white & black: 
      @n  e_red, e_orange, e_yellow, e_green, e_cyan, e_blue, e_purple, e_white, e_black
      @param r - pulse width value for red light
      @param g - pulse width of green light
      @param b - ulse width of blue light
    '''
    def set_RGB_color(self, color):
    def set_RGB_color(self, r, g, b):

    '''!
      @brief Get button status
      @return The current button status:
      @retval   true - the button is pressed
      @retval   false - the button is not pressed
    '''
    def get_button_status(self):

```


## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2022/05/17 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

