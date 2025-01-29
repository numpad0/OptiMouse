# OptiMouse
Arduino 1.x library for (wireless) mouse optical sensors

### Supported sensors 
- HP/Agilent/Avago/Broadcom ADNS-2051, ADNS-2083, ADNS-2610, ADNS-2620
- PixArt Imaging PAN3101
- Shenzhen LIZE MX8650 / SiGma Micro MX8650A

### Usage
Connect Vdd, GND, DATA, CLOCK pins to Arduino. Any I/O pins should work. Skip Vdd if mouse is using power from battery.
Supported mouse sensors can be found in many cheap *wireless* mouse - modern ultracheap wired mice tend to use all-in-one direct USB connections, and no longer has easy command interfaces. For harvesting, cheapest wireless mice you can find are recommended(wireless chip on the mouse must be removed for this library to work). 

### Raw image output
Very early HP/Agilent sensors had a raw image extraction debug command, which allowed a modified mouse to be used as a scanner. **None of modern mouse sensors support this feature**, likely due to security implications. This library just implements what commands are on datasheet, and cannot "force enable" such feature on modern sensors.

### Adding support for a new sensor
just fork this repository, copy MX8650A.cpp/MX8650A.h, do what you have to do, and upload what worked to your repository.

#### Credits
Original code by Martijn The  
Modified by zapmaker to (a) run on Arduino 1.x and (b) support 2620 sensor  
Modified by github.com/ax-iv to add PAN3101 support  
Modified by @numpad0 to add MX8650/MX8650A support
