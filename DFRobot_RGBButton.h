/*!
 * @file  DFRobot_RGBButton.h
 * @brief  Define infrastructure of DFRobot_RGBButton class
 * @details  Use I2C to control the RGB button module, set RGB LED color and get button press status.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-16
 * @url  https://github.com/DFRobot/DFRobot_RGBButton
 */
#ifndef __DFROBOT_RGBBUTTON_H__
#define __DFROBOT_RGBBUTTON_H__

#include <Arduino.h>
#include <Wire.h>


// #define ENABLE_DBG   //!< Open this macro and you can see the details of the program
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif


#define RGBBUTTON_DEFAULT_I2C_ADDR    uint8_t(0x2A)   ///< rgbbutton default i2c addr
#define RGBBUTTON_PART_ID          uint16_t(0x43DF)   ///< RGBButton chip ID

/* RGBButton register address */
#define RGBBUTTON_I2C_ADDR_REG        uint8_t(0x00)   ///< RGBButton I2C ADDR REG

#define RGBBUTTON_RED_REG             uint8_t(0x01)   ///< RGBButton RED REG
#define RGBBUTTON_GREEN_REG           uint8_t(0x02)   ///< RGBButton GREEN REG
#define RGBBUTTON_BLUE_REG            uint8_t(0x03)   ///< RGBButton BLUE REG

#define RGBBUTTON_BUTTON_SIGNAL_REG   uint8_t(0x04)   ///< RGBBUTTON BUTTON SIGNAL REG

#define RGBBUTTON_PID_MSB_REG         uint8_t(0x09)   ///< RGBButton PID MSB REG
#define RGBBUTTON_PID_LSB_REG         uint8_t(0x0A)   ///< RGBButton PID LSB REG

/* Convenience Macro */
#define RGBBUTTON_CONCAT_BYTES(msb, lsb)   (((uint16_t)msb << 8) | (uint16_t)lsb)   ///< Macro combines two 8-bit data into one 16-bit data


class DFRobot_RGBButton
{
public:

/************************* Interrupt Pin Configuration *******************************/

  /**
   * @enum  eGeneralRGBValue_t
   * @brief  RGB values for general seven colors and white & black
   */
  typedef enum
  {
    eRed    = 0xFF0000,   /**< Red */
    eOrange = 0xFF7F00,   /**< Orange */
    eYellow = 0xFFFF00,   /**< Yellow */
    eGreen  = 0x00FF00,   /**< Green */
    eCyan   = 0x00FFFF,   /**< Indigo */
    eBlue   = 0x0000FF,   /**< Blue */
    ePurple = 0x8B00FF,   /**< Purple */
    eWhite  = 0xFFFFFF,   /**< White (for turning on LED) */
    eBlack  = 0x000000,   /**< Black (for turning off LED) */
  }eGeneralRGBValue_t;

public:

/********************************* Init ***********************************/

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

/********************************* function ***********************************/

  /**
   * @fn setRGBColor
   * @brief Set the seven basic colors, and white & black (white and black correspond to turning LED on and off respectively) or set the corresponding colors by setting RGB values
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

protected:

  /**
   * @fn getI2CAddr
   * @brief Get the current I2C address of the module via I2C standard access
   * @return The current I2C address of the module
   */
  uint8_t getI2CAddr(void);

  /**
   * @fn getPID
   * @brief Get the product ID of the module
   * @return The product ID of the module
   */
  uint16_t getPID(void);

/************************** Register read/write port ******************************/

  /**
   * @fn writeReg
   * @brief Write register function
   * @param reg  Register address 8bits
   * @param pBuf Storage and buffer for data to be written
   * @param size Length of data to be written
   * @return None
   */
  void writeReg(uint8_t reg, const void* pBuf, size_t size);

  /**
   * @fn readReg
   * @brief Read register function
   * @param reg  Register address 8bits
   * @param pBuf Storage and buffer for data to be read
   * @param size Length of data to be read
   * @return Return the read length, returning 0 means reading failed
   */
  size_t readReg(uint8_t reg, void* pBuf, size_t size);

private:
  // Private variables
  TwoWire *_pWire;   // Pointer to I2C communication method
  uint8_t _deviceAddr;   // Address of the device for I2C communication
};

#endif
