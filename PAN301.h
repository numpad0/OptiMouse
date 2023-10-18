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
  public:
	PAN301(uint8_t, uint8_t);
	void updateStatus(void);
	signed char dx(void);
	signed char dy(void);
	uint8_t motion() const;
	uint8_t dxOverflow() const;
	uint8_t dyOverflow() const;

    uint8_t getLedShutterEnable();
    void setLedShutterEnable(uint8_t mode);
    uint8_t getXYQuadratureOutputEnable();
    void setXYQuadratureOutputEnable(uint8_t mode);
    
    void enterToSleep1();
    void enterToSleep2();
    void wakeUp();

    uint8_t getPowerDownMode();
    void setPowerDownMode(uint8_t mode);
    uint8_t getOutputResolution();
    void setOutputResolution(uint8_t mode);
};

#endif
