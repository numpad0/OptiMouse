/*
 ADNS2610.h - Part of optical mouse sensor library for Arduino
 Copyright (c) 2008 Martijn The.  All right reserved.
 http://www.martijnthe.nl/
 Conversion to Arduino 1.x by zapmaker (zapmaker.org)
 
 Based on sketches by Benoît Rousseau.
 
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

#ifndef MX8650A_h
#define MX8650A_h

#include <inttypes.h>
#include "OptiMouse.h"

class MX8650A : public OptiMouse
{
  private:
  public:
	MX8650A(uint8_t, uint8_t);
	signed char MX8650A::pid1(void);
	signed char MX8650A::pid2(void);
	signed char MX8650A::motionStatus(void);
	signed char MX8650A::dx(void);
	signed char MX8650A::dy(void);
	signed char MX8650A::operationMode(void);
	signed void MX8650A::setOperationMode(char OpMode);
	signed char MX8650A::configuration(void);
	signed void MX8650A::setConfiguration(char Conf);
	signed char MX8650A::imageQuality(void);
	signed char MX8650A::operationState(void);
	signed char MX8650A::writeProtect(void);
	signed void MX8650A::setWriteProtect(char Wp);
	signed char MX8650A::sleep1Setting(void);
	signed void MX8650A::setSleep1Setting(char Sp1Set);
	signed char MX8650A::enterTime(void);
	signed void MX8650A::setEnterTime(char EntTime);
	signed char MX8650A::sleep2Setting(void);
	signed void MX8650A::setSleep2Setting(char Sp2Set);
	signed char MX8650A::imageThreshold(void);
	signed void MX8650A::setImageThreshold(char ImgThr);
	signed char MX8650A::imageRecognition(void);
	signed void MX8650A::setImageRecognition(char ImgRcg);
};

#endif
