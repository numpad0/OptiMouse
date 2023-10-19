/*
 PAN301.h - Part of optical mouse sensor library for Arduino
 
 This sensor installed in Genius NetScroll+ Superior
 */

#ifndef PAN301_h
#define PAN301_h

#include "Arduino.h"
#include <inttypes.h>

#include "OptiMouse.h"

class PAN301 : public OptiMouse
{
  private:
	uint8_t _status;
    uint8_t _pdPin;
    uint8_t writeNumInByte(uint8_t source, uint8_t data, uint8_t numBit, uint8_t startBit);
  public:
    /**
    * @fn PAN301
    * @brief Create new PAN301 class object
    * @param sclkPin - SerialIO clock pin
    * @param sdioPin - SerialIO data pin
    * @return None
    */
	PAN301(uint8_t sclkPin, uint8_t sdioPin);
     /**
    * @fn PAN301
    * @brief Create new PAN301 class object
    * @param sclkPin - SerialIO clock pin
    * @param sdioPin - SerialIO data pin
    * @param pdPin - PowerDown pin
    * @return None
    */
    PAN301(uint8_t sclkPin, uint8_t sdioPin, uint8_t pdPin);

    /**
    * @fn productID
    * @brief Get Product ID 
    * @return uint16_t type, return Product ID.
    */
    uint16_t productID();
    /**
    * @fn updateStatus
    * @brief Update motion status - get data from Motion_Status register. After updateStatus call motion, dxOverflow, dyOverflow.
    * @return None
    */
	void updateStatus(void);
    /**
    * @fn dx
    * @brief X movement is counts since last report. Absolute value is determined by resolution. Reading clears the register. 
    * @return signed char,  Report range –128~+127.
    */
	signed char dx(void);
    /**
    * @fn dy
    * @brief Y movement is counts since last report. Absolute value is determined by resolution. Reading clears the register. 
    * @return signed char,  Report range –128~+127.
    */
	signed char dy(void);
    /**
    * @fn motion
    * @brief Motion indicator. Motion since last report or PD  
    * @return uint8_t, if motion - return 1.
    * @retval 0 - No motion
    * @retval 1 - Motion occurred, data ready for reading in Delta_X and Delta_Y registers
    */
	uint8_t motion() const;
    /**
    * @fn dxOverflow
    * @brief Motion Delta X overflow, dX buffer has overflowed since last report  
    * @return uint8_t, if overflow has occurred - return 1.
    * @retval 0 - No overflow
    * @retval 1 - Overflow has occurred
    */
	uint8_t dxOverflow() const;
    /**
    * @fn dyOverflow
    * @brief Motion Delta Y overflow, dX buffer has overflowed since last report  
    * @return uint8_t, if overflow has occurred - return 1.
    * @retval 0 - No overflow
    * @retval 1 - Overflow has occurred
    */
	uint8_t dyOverflow() const;
    /**
    * @fn getResolution
    * @brief Resolution in counts per inch  
    * @return uint8_t, Resolution type
    * @retval 0 - 800 (Default  @ PAN301ASI-208)
    * @retval 1 - 400 (Default  @ PAN301ASI-204) 
    * @retval 2 - 600
    */
    uint8_t getResolution();
    /**
    * @fn getLedShutterEnable
    * @brief Get LED shutter enable / disable  
    * @return uint8_t, LED shutter enable / disable
    * @retval 0 = Disable
    * @retval 1 = Enable 
    */
    uint8_t getLedShutterEnable();
    /**
    * @fn setLedShutterEnable
    * @brief Set LED shutter enable / disable  
    * @param mode 1：enable，0：disable 
    * @return None
    */
    void setLedShutterEnable(uint8_t mode);
    /**
    * @fn getXYQuadratureOutputEnable
    * @brief Get XY quadrature output enable/disable  
    * @return uint8_t, XY quadrature output enable/disable
    * @retval 0 = Disable
    * @retval 1 = Enable 
    */
    uint8_t getXYQuadratureOutputEnable();
    /**
    * @fn setXYQuadratureOutputEnable
    * @brief Set XY quadrature output enable/disable  
    * @param mode 1：enable，0：disable 
    * @return None
    */
    void setXYQuadratureOutputEnable(uint8_t mode);
    /**
    * @fn getSleepMode
    * @brief Get Sleep mode
    * @return uint8_t, sleep mode type
    * @retval 0 = Disable sleep
    * @retval 1 = Sleep mode 1
    * @retval 2 = Sleep mode 2
    */
    uint8_t getSleepMode();
    /**
    * @fn setSleepMode
    * @brief Set Sleep mode type
    * @param 0: Disable sleep, 1: Sleep mode 1, 2: Sleep mode 2
    * @return None    
    */
    void setSleepMode(uint8_t mode);
    /**
    * @fn enterToSleep1
    * @brief Force enter sleep mode 1. 
    * @return None.
    */
    void enterToSleep1();
    /**
    * @fn enterToSleep2
    * @brief Force enter sleep mode 2. 
    * @return None.
    */
    void enterToSleep2();
    /**
    * @fn wakeUp
    * @brief Force wakeup from sleep mode. 
    * @return None.
    */
    void wakeUp(bool physicalPin=false);
    /**
    * @fn getPowerDownMode
    * @brief Get Power down mode
    * @param physicalPin true: Use PD pin, 1: Use register
    * @return uint8_t, Power down mode type
    * @retval 0 = Normal operation (Default) 
    * @retval 1 = Power down mode
    */
    uint8_t getPowerDownMode();
    /**
    * @fn setPowerDownMode
    * @brief Set Power down mode
    * @param mode 0: Normal operation, 1: Power down
    * @return None    
    */
    void setPowerDownMode(uint8_t mode);
    /**
    * @fn powerDown
    * @brief Set Power down mode
    * @param mode 0: Normal operation, 1: Power down
    * @return None    
    */
    void powerDown(bool physicalPin=false);
    /**
    * @fn getOutputResolution
    * @brief Get Output resolution setting
    * @param physicalPin true: Use PD pin, 1: Use register
    * @return uint8_t, Output resolution type
    * @retval 0 = 800 (Default  @ PAN301ASI-208) 
    * @retval 1 = 400 (Default  @ PAN301ASI-204) 
    * @retval 2 = 600 
    */
    uint8_t getOutputResolution();
    /**
    * @fn setOutputResolution
    * @brief Set Output resolution setting
    * @param mode 0: 800, 1: 400, 2: 600
    * @return None    
    */
    void setOutputResolution(uint8_t mode);
    /**
    * @fn reSync
    * @brief Re-Synchronous Serial Interface
    * @return None    
    */
    void reSync(bool physicalPin=false);
    /**
    * @fn softReset
    * @param physicalPin true: Use PD pin, 1: Use register
    * @brief Soft Reset
    * @return None    
    */
    void softReset();
};

#endif
