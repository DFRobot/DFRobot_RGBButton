/*!
 * @file DFRobot_RGBButton.cpp
 * @brief  Define the infrastructure DFRobot_RGBButton class
 * @details  Use I2C to control the RGB button module, set RGB LED color and get button press status.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-17
 * @url https://github.com/DFRobot/DFRobot_RGBButton
 */
#include "DFRobot_RGBButton.h"

/********************************* Init ***********************************/

DFRobot_RGBButton::DFRobot_RGBButton(TwoWire *pWire, uint8_t i2cAddr)
{
  _deviceAddr = i2cAddr;
  _pWire = pWire;
}

bool DFRobot_RGBButton::begin(void)
{
  _pWire->begin();   // Wire.h(I2C)library function initialize wire library

  uint8_t idBuf[2];
  if(0 == readReg(RGBBUTTON_PID_MSB_REG, idBuf, sizeof(idBuf))) {   // Judge whether the data bus is successful
    DBG("ERR_DATA_BUS");
    return false;
  }

  DBG("real sensor id=");DBG(RGBBUTTON_CONCAT_BYTES(idBuf[0], idBuf[1]), HEX);
  if(RGBBUTTON_PART_ID != RGBBUTTON_CONCAT_BYTES(idBuf[0], idBuf[1])) {   // Judge whether the chip version matches
    DBG("ERR_IC_VERSION");
    return false;
  }

  DBG("begin ok!");
  return true;
}

/********************************** function **************************************/

void DFRobot_RGBButton::setRGBColor(eGeneralRGBValue_t color)
{
  uint8_t rgbBuf[3];
  rgbBuf[0] = (color >> 16) & 0xFF;
  rgbBuf[1] = (color >> 8) & 0xFF;
  rgbBuf[2] = color & 0xFF;
  writeReg(RGBBUTTON_RED_REG, rgbBuf, 3);
}

void DFRobot_RGBButton::setRGBColor(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t rgbBuf[3];
  rgbBuf[0] = r;
  rgbBuf[1] = g;
  rgbBuf[2] = b;
  writeReg(RGBBUTTON_RED_REG, rgbBuf, 3);
}

bool DFRobot_RGBButton::getButtonStatus(void)
{
  uint8_t buttonStatus;
  readReg(RGBBUTTON_BUTTON_SIGNAL_REG, &buttonStatus, 1);
  return buttonStatus ? true : false;
}

uint8_t DFRobot_RGBButton::getI2CAddr(void)
{
  uint8_t temp, i2cAddr;
  temp = _deviceAddr;
  _deviceAddr = 0;   // Common access address of I2C protocol
  readReg(RGBBUTTON_I2C_ADDR_REG, &i2cAddr, 1);
  _deviceAddr = temp;
  if(i2cAddr != _deviceAddr) {
    DBG(i2cAddr);
  }
  return i2cAddr;
}

uint16_t DFRobot_RGBButton::getPID(void)
{
  uint8_t pidBuf[2];
  readReg(RGBBUTTON_PID_MSB_REG, pidBuf, sizeof(pidBuf));
  return RGBBUTTON_CONCAT_BYTES(pidBuf[0], pidBuf[1]);
}

/************************** Register read/write port ******************************/

void DFRobot_RGBButton::writeReg(uint8_t reg, const void * pBuf, size_t size)
{
  if(pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pWire->setClock(100000);
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);

  for(size_t i = 0; i < size; i++) {
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

size_t DFRobot_RGBButton::readReg(uint8_t reg, void * pBuf, size_t size)
{
  size_t count = 0;
  if(NULL == pBuf) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pWire->setClock(100000);
  _pWire->beginTransmission(_deviceAddr);
  _pWire -> write(reg);
  if(0 != _pWire->endTransmission()) {   // Used Wire.endTransmission() to end a slave transmission started by beginTransmission() and arranged by write().
    DBG("endTransmission ERROR!!");
  } else {
    _pWire->requestFrom(_deviceAddr, (uint8_t)size);   // Master device requests size bytes from slave device, which can be accepted by master device with read() or available()
    
    while (_pWire->available()) {
      _pBuf[count++] = _pWire->read();   // Use read() to receive and put into buf
      // DBG(_pBuf[count-1], HEX);
    }
  }
  return count;
}
