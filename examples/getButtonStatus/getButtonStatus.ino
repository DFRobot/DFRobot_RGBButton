/*!
 * @file  getButtonStatus.ino
 * @brief  Button function demonstration
 * @details  The LED shows red light when the button is pressed, and turns off when released
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
DFRobot_RGBButton RGBButton(&Wire, /*I2CAddr*/ 0x2A);


void setup(void)
{
  Serial.begin(115200);

  /**
   * @brief Init function
   * @return bool type, true if successful, false if error
   */
  while( ! RGBButton.begin() ){
    Serial.println("Communication with device failed, please check connection!!!");
    delay(3000);
  }
  Serial.println("Begin ok!\n");

}

uint8_t flag = 0;

void loop()
{
  /**
   * @brief Get button status
   * @return The current button status:
   * @retval   true - the button is pressed
   * @retval   false - the button is not pressed
   */
  if( RGBButton.getButtonStatus() ) {
    flag = 1;
    /**
     * @brief Set the basic seven colors, and white & black (white and black correspond to LED on and off respectively)
     * @param color - The corresponding values of the basic seven colors and white & black (white and black correspond to LED on and off respectively): 
     * @n  eRed, eOrange, eYellow, eGreen, eCyan, eBlue, ePurple, eWhite, eBlack
     * @return None
     */
    RGBButton.setRGBColor(RGBButton.eRed);
    delay(50);
  } else if( 1 == flag ) {
    flag = 0;
    RGBButton.setRGBColor(RGBButton.eBlack);   // The LED is off when the button is released
  }
}
