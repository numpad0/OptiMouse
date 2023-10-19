/*
 PAN301.cpp - Part of optical mouse sensor library for Arduino
 Copyright (c) 2008 Martijn The.  All right reserved.
 http://www.martijnthe.nl/
 Conversion to Arduino 1.x by zapmaker (zapmaker.org)
 
 
 */

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "PAN301.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
#define Motion_Status		0x02

#define Delta_Y				0x03
#define Delta_X				0x04

#define Operation_Mode		0x05
#define Configuration_Register		0x06
/******************************************************************************
// Motion_Status Masks
******************************************************************************/
#define Mask_Motion			0x80
#define Mask_DYOVF			0x10
#define Mask_DXOVF			0x08
#define Mask_Resolution		0x06

/******************************************************************************
// Operation_Mode Masks
******************************************************************************/
/*LED shutter enable / disable 
0 = Disable 
1 = Enable (Default)*/
#define Mask_LEDsht_enh 	0x80
/*XY quadrature output enable/disable 
0 = Disable 
1 = Enable (Default)*/
#define Mask_XY_enh			0x40
/*Sleep mode enable/disable 
0 = Disable 
1 = Enable (Default)*/
#define Mask_Slp_enh		0x10
/*Automatic enter sleep2 mode enable/disable 
0 = Disable (Default) 
1 = Enable*/
#define Mask_Slp2au 		0x08
/*Manual enter sleep2 mode, set “1” will enter sleep2 and this bit will be reset to “0”*/
#define Mask_Slp2mu 		0x04
/*Manual enter sleep1 mode, set “1” will enter sleep2 and this bit will be reset to “0”*/
#define Mask_Slp1mu 		0x02
/*Manual wake up from sleep mode, set “1” will enter wakeup and this bit will be 
reset to “0”*/
#define Mask_Wakeup 		0x01

/******************************************************************************
 Configuration Masks
******************************************************************************/
/*Power down mode 
0 = Normal operation (Default) 
1 = Power down mode*/
#define Mask_PD         	0x08 
/*Output resolution setting 
0 = 800 (Default  @ PAN301ASI-208) 
1 = 400 (Default  @ PAN301ASI-204) 
2 = 600 */
#define Mask_RES			0x06

/******************************************************************************
 * Constructors
 ******************************************************************************/


PAN301::PAN301(uint8_t sclkPin, uint8_t sdioPin) : OptiMouse::OptiMouse(sclkPin, sdioPin)
{

}

PAN301::PAN301(uint8_t sclkPin, uint8_t sdioPin, uint8_t pdPin) : OptiMouse::OptiMouse(sclkPin, sdioPin)
{
    _pdPin=pdPin;
    pinMode (_pdPin, OUTPUT);
}

/******************************************************************************
 * Product_ID
 ******************************************************************************/
uint16_t PAN301::productID(){
    uint16_t res=0;
    uint8_t pid0=readRegister(0x0);
    uint8_t pid1=readRegister(0x1);
    res = pid0;
    res = (res<<6) | ((pid1 & 0b11111100)>>2);
    return res;
}

/******************************************************************************
// Delta_X
******************************************************************************/
signed char PAN301::dx(void)
{
	return (signed char) readRegister(Delta_X);
}
/******************************************************************************
// Delta_Y
******************************************************************************/

signed char PAN301::dy(void)
{
	return (signed char) readRegister(Delta_Y);
}
/******************************************************************************
// Motion Status 
Field: Motion[7]  Reserved[6:5]  DYOVF[4] DXOVF[3]  RES[2:1]  Reserved[0]
******************************************************************************/
void PAN301::updateStatus(void)
{
	_status = readRegister(Motion_Status);
}

uint8_t PAN301::motion() const
{
	return (uint8_t) (_status & Mask_Motion) == Mask_Motion;
}

uint8_t PAN301::dxOverflow() const
{
	return (uint8_t) (_status & Mask_DXOVF) == Mask_DXOVF;
}
uint8_t PAN301::dyOverflow() const
{
	return (uint8_t) (_status & Mask_DYOVF) == Mask_DYOVF;
}
uint8_t PAN301::getResolution(){
    uint8_t _motion = readRegister(Motion_Status);
    return (uint8_t) (_motion & Mask_Resolution) >> 1;
}

/******************************************************************************
// Operation Mode 
******************************************************************************/
uint8_t PAN301::getLedShutterEnable(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    return (uint8_t) (_op_mode & Mask_LEDsht_enh) >> 7;
}

void PAN301::setLedShutterEnable(uint8_t mode){
    if(mode<2){
        uint8_t _op_mode = readRegister(Operation_Mode);
        _op_mode=writeNumInByte(_op_mode,mode,1,7);
        writeRegister(Operation_Mode,_op_mode);
    }
}

uint8_t PAN301::getXYQuadratureOutputEnable(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    return (uint8_t) (_op_mode & Mask_XY_enh) >> 6;
}

void PAN301::setXYQuadratureOutputEnable(uint8_t mode){
    if(mode<2){
        uint8_t _op_mode = readRegister(Operation_Mode);
        _op_mode=writeNumInByte(_op_mode,mode,1,6);
        writeRegister(Operation_Mode,_op_mode);
    }
}

uint8_t PAN301::getSleepMode(){ 
    // Return   0 - sleep_mode disable
    //          1 - sleep_mode_1
    //          2 - sleep_mode_2
    uint8_t _op_mode = readRegister(Operation_Mode);
    _op_mode = (_op_mode & 0b00011000) >> 3;
    return (uint8_t) _op_mode==0?0:_op_mode-1;    
}

void PAN301::setSleepMode(uint8_t mode){ 
    // mode     0 - sleep_mode disable
    //          1 - sleep_mode_1
    //          2 - sleep_mode_2
    uint8_t _op_mode = readRegister(Operation_Mode);
    if(mode==0)    
        _op_mode=writeNumInByte(_op_mode,0b0,1,4);
    else
    {
        _op_mode=writeNumInByte(_op_mode,mode+1,2,3);
    }
    return (uint8_t) _op_mode==0?0:_op_mode-1;    
}


void PAN301::enterToSleep1(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    _op_mode=writeNumInByte(_op_mode,0b1,1,4);
    _op_mode=writeNumInByte(_op_mode,0b010,1,0);
    writeRegister(Operation_Mode,_op_mode);
}

void PAN301::enterToSleep2(){
    uint8_t _op_mode = readRegister(Operation_Mode);    
    _op_mode=writeNumInByte(_op_mode,0b1,1,4);
    _op_mode=writeNumInByte(_op_mode,0b100,1,0);
    writeRegister(Operation_Mode,_op_mode);
}

void PAN301::wakeUp(bool physicalPin=false){
    if(physicalPin==true)
        digitalWrite(_pdPin,LOW);
    else
    {
        uint8_t _op_mode = readRegister(Operation_Mode);    
        _op_mode=writeNumInByte(_op_mode,0b1,1,0);
        writeRegister(Operation_Mode,_op_mode);
    }
    delay(3);
}

/******************************************************************************
 Configuration 
 Field: Reserved[7:4]  PD[3] RES[2:1] Reserved[0]
******************************************************************************/

uint8_t PAN301::getPowerDownMode(){
    uint8_t _config = readRegister(Configuration_Register);
    return (uint8_t) (_config & Mask_PD) >> 3;
}

void PAN301::setPowerDownMode(uint8_t mode){
    if(mode<2){
        uint8_t _config = readRegister(Configuration_Register);
        _config=writeNumInByte(_config,mode,1,3);
        writeRegister(Configuration_Register,_config);
    }
}

 void PAN301::powerDown(bool physicalPin=false){
    if(physicalPin==true){
        digitalWrite(_pdPin,HIGH);
        delay(1);
    }
    else
        setPowerDownMode(1);
 }


uint8_t PAN301::getOutputResolution(){
    uint8_t _config = readRegister(Configuration_Register);
    return (uint8_t) (_config & Mask_RES) >> 1;
}

void PAN301::setOutputResolution(uint8_t mode){
    if(mode<3){
        uint8_t _config = readRegister(Configuration_Register);
        _config=writeNumInByte(_config,mode,2,1);
        writeRegister(Configuration_Register,_config);
    }
}

void PAN301::reSync(bool physicalPin=false){
    if(physicalPin){
        digitalWrite(_pdPin, HIGH);                     
        delayMicroseconds(2);
        digitalWrite(_pdPin, LOW);
        digitalWrite(_sclkPin, LOW);                     
        delayMicroseconds(1);
        digitalWrite(_sclkPin, HIGH);                     
    }
    else{
        digitalWrite(_sclkPin, HIGH);                     
        delayMicroseconds(1);
        digitalWrite(_sclkPin, LOW);
        delayMicroseconds(2);
        digitalWrite(_sclkPin, HIGH);                     
        delay(2);
    }

}
void PAN301::softReset(){
    digitalWrite(_sclkPin, LOW);
    delayMicroseconds(1);
    digitalWrite(_pdPin, HIGH);
	delayMicroseconds(2);
	digitalWrite(_pdPin, LOW);    
    delayMicroseconds(1);
    digitalWrite(_sclkPin, HIGH);

}
// Private Methods /////////////////////////////////////////////////////////////
uint8_t PAN301::writeNumInByte(uint8_t source, uint8_t data, uint8_t numBit, uint8_t startBit){  
  uint8_t res=source;
  for(uint8_t i=startBit;i<startBit+numBit;i++)
    if (data & (1 << i-startBit)) res = res | (1 << i); else res = res & (~(1 << i));
  return res;
}


