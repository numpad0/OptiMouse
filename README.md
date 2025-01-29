# OptiMouse
Arduino 1.x library for wireless mouse optical mouse sensors

### Supported sensors 
- HP/Agilent/Avago/Broadcom ADNS-2051, ADNS-2083, ADNS-2610, ADNS-2620
- PixArt Imaging PAN3101
- Shenzhen LIZE MX8650 / SiGma Micro MX8650A

### Usage
Connect Vdd, GND, DATA, CLOCK pins to Arduino. Any of I/O pins should work.
Supported mouse sensors can be found in many cheap wireless mouse - modern ultracheap wired mice tend to use all-in-one direct USB connections, and no longer has easy command interfaces. For harvesting, cheap *wireless* mice are recommended. 

### Adding support for a new sensor
just fork this repository, copy MX8650A.cpp/MX8650A.h, do what you have to do and upload what worked to your repository.

#### Credits
Original code by Martijn The  
Modified by zapmaker to (a) run on Arduino 1.x and (b) support 2620 sensor  
Modified by github.com/ax-iv to add PAN3101 support  
Modified by @numpad0 to add MX8650/MX8650A support
