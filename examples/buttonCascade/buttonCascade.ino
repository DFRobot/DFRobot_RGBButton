/*!
 * @file  buttonCascade.ino
 * @brief  Button cascade function demonstration
 * @details  Cascade 3 button modules via I2C, the 3 modules all show white LEDs by default. When button pressed, they change to red, green, and blue correspondingly.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-17
 * @url  https://github.com/DFRobot/DFRobot_RGBButton
 */
#include <DFRobot_RGBButton.h>


/**
 * Instantiate an object to drive our sensor;
 * Set address according to encoder DIP switch
 * (the setting takes effect after encoder power fail and restart):
 * | A2 | A1 | A0 | ADDR |
 * |----|----|----|------|
 * | 0  | 0  | 0  | 0x23 |
 * | 0  | 0  | 1  | 0x24 |
 * | 0  | 1  | 0  | 0x25 |
 * | 0  | 1  | 1  | 0x26 |
 * | 1  | 0  | 0  | 0x27 |
 * | 1  | 0  | 1  | 0x28 |
 * | 1  | 1  | 0  | 0x29 |
 * | 1  | 1  | 1  | 0x2A |
 */
DFRobot_RGBButton RGBButton1(&Wire, /*I2CAddr*/ 0x23);   // button 1
DFRobot_RGBButton RGBButton2(&Wire, /*I2CAddr*/ 0x24);   // button 2
DFRobot_RGBButton RGBButton3(&Wire, /*I2CAddr*/ 0x25);   // button 3


void setup(void)
{
  Serial.begin(115200);

  /**
   * @brief Init function
   * @return bool type, true if successful, false if error
   */
  while( ! RGBButton1.begin() ){
    Serial.println("Communication with device failed, please check connection!");
    delay(3000);
  }
  while( ! RGBButton2.begin() ){
    Serial.println("Communication with device failed, please check connection!");
    delay(3000);
  }
  while( ! RGBButton3.begin() ){
    Serial.println("Communication with device failed, please check connection!");
    delay(3000);
  }
  Serial.println("Begin ok!\n");

  /**
   * @brief Set the basic seven colors, and white & black (white and black correspond to LED on and off respectively)
   * @param color - The corresponding values of the basic seven colors and white & black (white and black correspond to LED on and off respectively): 
   * @n  eRed, eOrange, eYellow, eGreen, eCyan, eBlue, ePurple, eWhite, eBlack
   * @return None
   */
  RGBButton1.setRGBColor(RGBButton1.eWhite);
  RGBButton2.setRGBColor(RGBButton2.eWhite);
  RGBButton3.setRGBColor(RGBButton3.eWhite);
}

uint8_t flag1 = 0, flag2 = 0, flag3 = 0;

void loop()
{
  /**
   * @brief Get button status
   * @return The current button status:
   * @retval   true - the button is pressed
   * @retval   false - the button is not pressed
   */
  if( RGBButton1.getButtonStatus() ) {   // button 1, show red LED when pressed
    flag1 = 1;
    RGBButton1.setRGBColor(RGBButton1.eRed);
    delay(50);
  } else if( 1 == flag1 ) {
    flag1 = 0;
    RGBButton1.setRGBColor(RGBButton1.eWhite);
  }

  if( RGBButton2.getButtonStatus() ) {   // button 2, show green LED when pressed
    flag2 = 1;
    RGBButton2.setRGBColor(RGBButton2.eGreen);
    delay(50);
  } else if( 1 == flag2 ) {
    flag2 = 0;
    RGBButton2.setRGBColor(RGBButton2.eWhite);
  }

  if( RGBButton3.getButtonStatus() ) {   // button 3, show blue LED when pressed
    flag3 = 1;
    RGBButton3.setRGBColor(RGBButton3.eBlue);
    delay(50);
  } else if( 1 == flag3 ) {
    flag3 = 0;
    RGBButton3.setRGBColor(RGBButton3.eWhite);
  }
}
