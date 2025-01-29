/*
 OptiMouse.cpp - Part ofoptical mouse sensor library for Arduino
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

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "OptiMouse.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/

OptiMouse::OptiMouse(uint8_t sclkPin, uint8_t sdioPin)
{
  _sclkPin = sclkPin;
  _sdioPin = sdioPin;
  pinMode (_sclkPin, OUTPUT);
  pinMode (_sdioPin, INPUT);
}


/******************************************************************************
 * User API
 ******************************************************************************/

void OptiMouse::begin(void)
{
	// Re-sync (see datasheet �5.4):
	// Toggle the SLCK line from high to low to high....
	digitalWrite(_sclkPin, HIGH);                     
	delayMicroseconds(5);
	digitalWrite(_sclkPin, LOW);
	delayMicroseconds(1);
	digitalWrite(_sclkPin, HIGH);
	
	// Wait at least tSIWTT (0.9 second?) for the
	// OptiMouse serial transaction timer to time out:
	delay(10);
}

// Private Methods /////////////////////////////////////////////////////////////


uint8_t OptiMouse::readRegister(uint8_t address)
{
	int i = 7;
	uint8_t value=0;
	
	// Write the address of the register we want to read:
	pinMode (_sdioPin, OUTPUT);
	digitalWrite(_sclkPin, HIGH); //Make sure the clock is high.
    address &= 0x7F;    //Make sure the highest bit of the address byte is '0' to indicate a read.
 
    //Send the Address 
    for(int address_bit=7; address_bit >=0; address_bit--){
        digitalWrite(_sclkPin, LOW);  //Lower the clock
        pinMode(_sdioPin, OUTPUT); //Make sure the SDIO pin is set as an output.
        
        //If the current bit is a 1, set the SDIO pin. If not, clear the SDIO pin
        if(address & (1<<address_bit)){
            digitalWrite(_sdioPin, HIGH);
        }
        else{
            digitalWrite(_sdioPin, LOW);
        }
        delayMicroseconds(10);
        digitalWrite(_sclkPin, HIGH);
        delayMicroseconds(10);
    }
    
    delayMicroseconds(120);   //Allow extra time for ADNS2620 to transition the SDIO pin (per datasheet)
    //Make SDIO an input on the microcontroller
    pinMode(_sdioPin, INPUT);	//Make sure the SDIO pin is set as an input.
	digitalWrite(_sdioPin, HIGH); //Enable the internal pull-up
        
    //Send the Value byte to the ADNS2620
    for(int value_bit=7; value_bit >= 0; value_bit--){
        digitalWrite(_sclkPin, LOW);  //Lower the clock
        delayMicroseconds(10); //Allow the ADNS2620 to configure the SDIO pin
        digitalWrite(_sclkPin, HIGH);  //Raise the clock
        delayMicroseconds(10);
        //If the SDIO pin is high, set the current bit in the 'value' variable. If low, leave the value bit default (0).    
		//if((ADNS_PIN & (1<<_sdioPin)) == (1<<_sdioPin))value|=(1<<value_bit);
		if(digitalRead(_sdioPin))value |= (1<<value_bit);

    }
    
    return value;
}

void OptiMouse::writeRegister(uint8_t address, uint8_t data)
{
	int i = 7;
	
	// Set MSB high, to indicate write operation:
	address |= 0x80;
	
	// Write the address:
	pinMode(_sdioPin, OUTPUT);	//Make sure the SDIO pin is set as an output.
    	digitalWrite(_sclkPin, HIGH);
	for (; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
		delayMicroseconds(10);
		digitalWrite (_sdioPin, address & (1 << i));
		delayMicroseconds(10);
		digitalWrite (_sclkPin, HIGH);
		delayMicroseconds(10);
	}
	
	// Write the data:
	for (i=7; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
		digitalWrite (_sdioPin, data & (1 << i));
		delayMicroseconds(10);
		digitalWrite (_sclkPin, HIGH);
		delayMicroseconds(10);
	}
}
