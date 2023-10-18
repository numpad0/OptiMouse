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
#define Product_ID			0x00

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

/******************************************************************************
 * User API
 ******************************************************************************/

void PAN301::updateStatus(void)
{
	_status = readRegister(Motion_Status);
}

signed char PAN301::dx(void)
{
	return (signed char) readRegister(Delta_X);
}

signed char PAN301::dy(void)
{
	return (signed char) readRegister(Delta_Y);
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
        _op_mode |= mode<<7;
        writeRegister(_op_mode)
    }
}

uint8_t PAN301::getXYQuadratureOutputEnable(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    return (uint8_t) (_op_mode & Mask_XY_enh) >> 6;
}

void PAN301::setXYQuadratureOutputEnable(uint8_t mode){
    if(mode<2){
        uint8_t _op_mode = readRegister(Operation_Mode);
        _op_mode |= mode<<6;
        writeRegister(_op_mode)
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
        
    else
    _op_mode |= (_op_mode & 0b00011000) >> 3;
    return (uint8_t) _op_mode==0?0:_op_mode-1;    
}


void PAN301::enterToSleep1(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    _op_mode |= 0b00010010;
    writeRegister(_op_mode)
}

void PAN301::enterToSleep2(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    _op_mode |= 0b00010100;
    writeRegister(_op_mode)
}

void PAN301::wakeUp(){
    uint8_t _op_mode = readRegister(Operation_Mode);
    _op_mode |= 0x1;
    writeRegister(_op_mode)
}

/******************************************************************************
 Configuration 
******************************************************************************/

uint8_t PAN301::getPowerDownMode(){
    uint8_t _config = readRegister(Configuration_Register);
    return (uint8_t) (_config & Mask_PD) >> 3;
}

void PAN301::setPowerDownMode(uint8_t mode){
    if(mode<2){
        uint8_t _config = readRegister(Configuration_Register);
        _config |= mode<<3;
        writeRegister(_config)
    }
}

uint8_t PAN301::getOutputResolution(){
    uint8_t _config = readRegister(Configuration_Register);
    return (uint8_t) (_config & Mask_RES) >> 1;
}

void PAN301::setOutputResolution(uint8_t mode){
    if(mode<3){
        uint8_t _config = readRegister(Configuration_Register);
        _config |= mode<<1;
        writeRegister(_config)
    }
}

// Private Methods /////////////////////////////////////////////////////////////

