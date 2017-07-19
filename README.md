# Lego_Monster_Truck
Building a Lego Monster Truck with PulseRain M10, please visit the following for more information:

https://hackaday.io/project/20493-play-fpga-like-arduino/log/62770-stick-shift-lego-monster-truck

http://limerick.pulserain.com/2017/07/how-to-build-lego-monster-truck.html

=================

This repository contains the firmware and host python script for [building a stick shift Lego Monster Truck](https://hackaday.io/project/20493-play-fpga-like-arduino/log/62770-stick-shift-lego-monster-truck) 

### Firmware:
*) open the Truck_Firmware/Truck_Firmware.ino in Arduino IDE. Press "CTRL-R" to build it

*) find the .hex file in correspondent Arduino folder (You can find the folder name by turnning on verbose output in Arduino IDE)

*) power off the M10 board

*) put a jumper to JP6 

*) reconnect the USB cable. Use M10_config_gui.exe (https://github.com/PulseRain/Mustang/raw/master/synth/output_files/M10_config_gui.exe) to program the .hex file into M10 board

*) Power off M10 board again remove the jumper. And put everything back together.


### Host Python Script:

*) Turn on power of Lego Monster Truck. Make sure the blue LED on ESP8266 shield is blinking. 

*) (Assume a Windows Laptop is being used.) Turn on the Wifi. look for an AP name "LEGO8266A". Password is "1234567890", or whatever configured by the firmware

*) After the Wifi is connected. Open a command prompt and run the python script "ESP8266_Console.py"

*) If the Wifi is not configured properly, the script will quit with a socket exception. Otherwise, it will prompt you to key in the control. Use I/J/K/M (case sensitive) for Forward/Left/Right/Back. Use space to stop. And press "ctrl-D" three times to exit the script


### Control with Joystick:
With the help of JoyToKey (http://joytokey.net/en/), you can use a joystick to replace the key stroke.

Have Fun!
