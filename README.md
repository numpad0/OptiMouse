# OptiMouse
Arduino 1.x library for (wireless) mouse optical sensors

### Supported sensors 
- HP/Agilent/Avago/Broadcom ADNS-2051, ADNS-2083, ADNS-2610, ADNS-2620
- PixArt Imaging PAN3101
- Shenzhen LIZE MX8650 / SiGma Micro MX8650A

### Usage
Connect Vdd, GND to either 3V3 or 5V pins on an Arduino for power(chip dependent). Connect DATA, CLOCK pins to an I/O pin of choice on an Arduino. Any I/O pins should work. Skip Vdd if mouse is using power from battery, but keep GND-GND connection. If you don't, currents through DATA/CLOCK pins would go through AC adapters, and you might not want that.
Supported mouse sensors can be found in many cheap *wireless* mouse - modern ultracheap *wired* mice tend to be all-in-one direct USB solutions, and no longer has easy command interfaces. For harvesting, cheapest wireless mice you can find are recommended(wireless chip on the mouse must be removed for this library to work). 

### Raw image output
Very early HP/Agilent sensors had a raw image extraction debug command, which allowed a modified mouse to be used as a scanner. **None of modern mouse sensors support this feature**, likely due to security implications. This library just implements what commands are on datasheet, and cannot "force enable" such feature on modern sensors.

### Adding support for a new sensor
just fork this repository, copy MX8650A.cpp/MX8650A.h, do what you have to do, and upload what worked to your repository.

#### Potentially compatible sensors
Below is a list of compatible sensors taken from Telink TLSR8510/TLSR8513 datasheet; there are chances that these sensors might just work with MX8650A code. Report in issues if any of it did/not:

- PixArt PAN3204DB, PAN3204L, PAN3204LL, PAN3204UL, PAN3205, PAN3207
- SiGma Micro MX8630, MX8630A, MX8640, MX8650A
- ELAN Microelectronics Corp. OM15, OM16
- PixArt PAW3212
- "VT108", Shenzhen Fuman KA8
- PixArt FCT3065
- "FH8835"
- Yspring YS8008
- "S8321"
  
(also refer to https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor/)

#### Credits
Original code by Martijn The  
Modified by zapmaker to (a) run on Arduino 1.x and (b) support 2620 sensor  
Modified by github.com/ax-iv to add PAN301 support  
Modified by @numpad0 to add MX8650/MX8650A support
