/*
 ADNS2083.cpp - Part of optical mouse sensor library for Arduino
 Copyright (c) 2008 Martijn The.  All right reserved.
 http://www.martijnthe.nl/
 Conversion to Arduino 1.x by zapmaker (zapmaker.org)
 
 Based on sketches by Beno�t Rousseau.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 MX8650A.cpp: modified from above by @numpad0 (c)2025
 note: "default" vs 0b000... disagreements are per datasheet
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "Arduino.h"
#include "OptiMouse.h"
#include "MX8650A.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

#define Product_ID1			0x00
#define Product_ID2			0x01
#define Motion_Status		0x02
#define Delta_X				0x03
#define Delta_Y				0x04
#define Operation_Mode		0x05
#define Configuration		0x06
#define Image_Quality		0x07
#define Operation_State		0x08
#define Write_Protect		0x09
#define Sleep1_Setting		0x0A
#define Enter_Time			0x0B
#define Sleep2_Setting		0x0C
#define Image_Threshold		0x0D
#define Image_Recognition	0x0E


/******************************************************************************
 * Constructors
 ******************************************************************************/


MX8650A::MX8650A(uint8_t sclkPin, uint8_t sdioPin) : OptiMouse::OptiMouse(sclkPin, sdioPin)
{

}

/******************************************************************************
 * User API
 ******************************************************************************/
signed char MX8650A::pid1(void)
{
	return (signed char) readRegister(Product_ID1);
	// Default: 0x30
}

signed char MX8650A::pid2(void)
{
	return (signed char) readRegister(Product_ID2);
	// Default: 0x5X
}

signed char MX8650A::motionStatus(void)
{
	return (signed char) readRegister(Motion_Status);
	// Default: -
	// Motion  Rsvd  Rsvd  DYOvf  DxOvf   1  Res1  Res2
	//   1|0    x     x    Overflow(1|0)  1  Resolution
	//
	// Resolution: 00:800, 01:1000, 10: 1200, 11:1600CPI
}

signed char MX8650A::dx(void)
{
	return (signed char) readRegister(Delta_X);
	// Default: -
}

signed char MX8650A::dy(void)
{
	return (signed char) readRegister(Delta_Y);
	// Default: -
}

signed char MX8650A::operationMode(void)
{
	return (signed char) readRegister(Operation_Mode);
	// Default: 0xB8
	//
	// LED_CTR 0    1   SLP_EN  SLP2_EN SLP2MU  SLP1MU  WAKEUP
	//  1      0    1    1       1       0       0       0
}

signed void MX8650A::setOperationMode(char OpMode)
{
	writeRegister(Operation_Mode, OpMode);
	// Default: 0xB8
	//
	// LED_CTR: LED Shutter
	// 0      : 0
	// 1      : 1
	// SLP_EN : enable sleep 1(light sleep)
	// SLP2_EN: enable sleep 2(deeper sleep) 
	// SLP2MU : trigger sleep 2
	// SLP1MU : trigger sleep 1
	// WAKEUP : force wakeup
}

signed char MX8650A::configuration(void)
{
	return (signed char) readRegister(Configuration);
	// Default: 0x04
	//
	// RESET  MOTSWK   0      0     PD_EN   1    CPI1   CPI0
	//  0      0       0      0      0      1     0      0
}

signed void MX8650A::setConfiguration(char Conf)
{
	writeRegister(Operation_Mode, Conf);
	// Default: 0x04
	//
	// RESET : trigger chip reset
	// MOTSWK: if set, MOTSWK pin outputs wake pulse
	// 0     : 0
	// 0     : 0
	// PD_EN : power down if set
	// 1     : 1
	// CPI1  :  00,   01,   10,   11
	// CPI0  : 800, 1000, 1200, 1600
}

signed char MX8650A::imageQuality(void)
{
	return (unsigned char) readRegister(Image_Quality);
	// Default: -
	//
	// 0x00 - 0xFF
	// if(imgth > imgqual) return(counts); else return(void);
}

signed char MX8650A::operationState(void)
{
	return (signed char) readRegister(Operation_State);
	// Default: -
	//
	// Rsvd Rsvd Rsvd Rsvd SLP_STATE OPSTATE2 OPSTATE1 OPSTATE0
	//  x    x    x    x    0         0        0        0
	//
	// SLP_STATE: (0|1) = (sleep1|sleep2)
	// OPSTATE  : 000 -> normal
	//            001 -> onSleep1()
	//            010 -> onSleep2()
	//            011 -> Rsvd
	//            100 -> in sleep
}

signed char MX8650A::writeProtect(void)
{
	return (signed char) readRegister(Write_Protect);
	// Default: 0x00
	//
	// WP7 WP6 WP5 WP4 WP3 WP2 WP1 WP0 
	// 0x00: all locked
	// 0x5A: unlocked
}

signed void MX8650A::setWriteProtect(char Wp)
{
	writeRegister(Write_Protect, Wp);
	// Default: 0x00
	//
	// 0x00 | 0x5A
}

signed char MX8650A::sleep1Setting(void)
{
	return (signed char) readRegister(Sleep1_Setting);
	// Default: 0x72
	//
	// S1FREQ3 S1FREQ2 S1FREQ1 S1FREQ0  0  0  1  0
	//  0       1       1       1       0  0  1  0
}

signed void MX8650A::setSleep1Setting(char Sp1Set)
{
	writeRegister(Sleep1_Setting, Sp1Set);
	// Default: 0x72
	//
	// sets sleep1 check frequency by 4ms increment
	// (1 + S1FREQ) * 4[ms], 4 < freq < 64[ms]
	// default 32ms
}

signed char MX8650A::enterTime(void)
{
	return (signed char) readRegister(Enter_Time);
	// Default: 0x12
	//
	// S1ETM3 S1ETM2 S1ETM1 S1ETM0 S2ETM3 S2ETM2 S2ETM1 S2ETM0
	//  0      0      0      1      0      0      1      0   
}

signed void MX8650A::setEnterTime(char EntTime)
{
	writeRegister(Enter_Time, EntTime);
	// Default: 0x12
	//
	// Sleep 1 timeout 
	// = (1 + S1ETM) * 128[ms], 128 < S1 timeout < 2048[ms]
	// default 256ms(0.25s), max 2048ms(2s)
	//
	// Sleep 2 timeout
	// = (1 + S2ETM) * 20480[ms], 20480 < S2 < 327680[ms]
	// default 61440ms(61s), max 327680ms(5.46min)
}

signed char MX8650A::sleep2Setting(void)
{
	return (signed char) readRegister(Sleep2_Setting);
	// Default: 0x92
	//
	// S2FREQ3 S2FREQ2 S2FREQ1 S2FREQ0  0  0  1  0
	//  1       0       0       1       0  0  1  0
}

signed void MX8650A::setSleep2Setting(char Sp2Set)
{
	writeRegister(Sleep2_Setting, Sp2Set);
	// Default: 0x92
	//
	// sets sleep2 check frequency by 32ms increment
	// (1 + S2FREQ) * 32[ms], 32 < freq < 512[ms]
	// default 320ms
}

signed char MX8650A::imageThreshold(void)
{
	return (signed char) readRegister(Image_Threshold);
	// Default: 0x10
	//
	// IMGTH7 - IMGTH 0
	// 0b00010000
}

signed void MX8650A::setImageThreshold(char ImgThr)
{
	writeRegister(Image_Threshold, ImgThr);
	// Default: 0x10
	//
	// if(imgth > imgqual) return(counts); else return(void);
}

signed char MX8650A::imageRecognition(void)
{
	return (signed char) readRegister(Image_Recognition);
	// Default: 0xA9
	//
	// PK_WT2 PK_WT1 PK_WT0 0   IMGQADF3 IMGQADF2 IMGQADF1 IMGQADF0
	//  1      0      1     0    1        0        0        1
}

signed void MX8650A::setImageRecognition(char ImgRcg)
{
	writeRegister(Image_Recognition, ImgRcg);
	// Default: 0xA9
	//
	// PK_WT  : Peak threshold weighting
	//          higher value = higher recognition rate(?) 
	// 
	// IMGQADF: Image qualification threshold difference
	//          higher value = higher recognition rate(?)
}

// Private Methods /////////////////////////////////////////////////////////////

