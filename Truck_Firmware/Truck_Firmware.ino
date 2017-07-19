/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#include "M10PWM.h"
#include "M10SerialAUX.h"
#include "string.h"
#include "M10ESP8266.h"


uint8_t drive_force = 0;
int8_t c_prev = ' ';

#define delta  80
const uint8_t force_limit =  delta * 3;



//----------------------------------------------------------------------------
// keyTrack()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      Function to execute the key stroke command received from Wifi
//----------------------------------------------------------------------------
int16_t keyTrack()
{
  uint8_t c;
  

  while (SerialAUX.available()) {
    c_prev = c; 
    c = SerialAUX.read();
    switch (c) {
      case 'T':
          //Serial.write("T");
          PWM.dutyCycle(0, 0, 255);
          drive_force = 0;
          esp8266RxBuffer[esp8266bufferHead++] = c;
          break;
      
      case 'F':
          //Serial.write("F");
          digitalWrite(12, LOW);

          if (c_prev == c) {
            if (drive_force < force_limit) { 
                drive_force += delta;
            }
          } else {
                drive_force = delta;     
          }

          PWM.dutyCycle(0, drive_force, 60);
     
          esp8266RxBuffer[esp8266bufferHead++] = c;
          break;
      
      case 'B':
          //Serial.write("B");
           digitalWrite(12, HIGH);

           if (c_prev == c) {
              
              if (drive_force < force_limit) {
                  drive_force += delta;
              }
           } else {
                 drive_force = delta;     
           }
      
           PWM.dutyCycle(0, drive_force, 60);
           
           esp8266RxBuffer[esp8266bufferHead++] = c;
           break;

      case 'L':
          //Serial.write("L");
          esp8266RxBuffer[esp8266bufferHead++] = c;
          
          digitalWrite(13, 1);
          PWM.dutyCycle (5, 200, 80);
          delay(500);
          PWM.dutyCycle (5, 0, 120);
          break;

      case 'R':
          //Serial.write("R");
          esp8266RxBuffer[esp8266bufferHead++] = c;

          digitalWrite(13, 0);
          PWM.dutyCycle (5, 200, 80);
          delay(500);
          PWM.dutyCycle (5, 0, 120);

          break;
      
      case 'S':
          PWM.dutyCycle(0, 0, 255);
          drive_force = 0;
          //Serial.write("S");
          esp8266RxBuffer[esp8266bufferHead++] = c;
          break;
          
    } // End of switch()
          
  } // End of while loop
} // keyTrack()


//----------------------------------------------------------------------------
// setup()
//----------------------------------------------------------------------------

void setup() 
{

    int16_t ret;
    PWM.resolution(0, 32768);
    PWM.resolution(5, 32768);
    PWM.dutyCycle(0, 0, 255);
    PWM.dutyCycle (5, 0, 80);
    delay(2000);
    Serial.begin(115200);
    SerialAUX.begin(9600);
    delay(1000);
    pinMode (12, OUTPUT);
    digitalWrite(12, LOW);
    
    pinMode (13, OUTPUT);
 
  

    ESP8266.resetESP8266();
    Serial.write(esp8266RxBuffer);

    delay(1000);

    //== run the following only once to setup the AP name 
    // commandResponse(ESP8266_AP_CONFIG, ESP8266_CMD_SETUP, "\"LEGO8266A\",\"1234567890\",6,3");
    // Serial.write(esp8266RxBuffer);

 
    ESP8266.commandResponse(ESP8266_WIFI_MODE, ESP8266_CMD_SETUP, "2"); 
    Serial.write(esp8266RxBuffer);

    delay(100);
    ESP8266.commandResponse(ESP8266_DHCP, ESP8266_CMD_SETUP, "0,1");
    Serial.write(esp8266RxBuffer);

    delay(100);
    
    ESP8266.setMux(1);
    Serial.write(esp8266RxBuffer);

    ESP8266.configureTCPServer("1,80");
    Serial.write(esp8266RxBuffer);

    
    ESP8266.commandResponse(ESP8266_TCP_SERVER_TIMEOUT, ESP8266_CMD_SETUP, "0");
    Serial.write(esp8266RxBuffer);


    ESP8266.commandResponse(ESP8266_GET_LOCAL_IP, ESP8266_CMD_EXECUTE, 0);
    Serial.write(esp8266RxBuffer);

 //   commandResponse(ESP8266_UART_CUR, ESP8266_CMD_SETUP, "921600,8,1,0,0");
 //   Serial.write(esp8266RxBuffer);
 //   SerialAUX.begin(921600);
    delay(1000);  
  
} // setup()

//----------------------------------------------------------------------------
// loop()
//----------------------------------------------------------------------------

void loop()
{
  uint8_t *t;
  int16_t ret;

  ESP8266.clearBuffer();
  keyTrack();
  delay(1000);
  
} // End of loop()

