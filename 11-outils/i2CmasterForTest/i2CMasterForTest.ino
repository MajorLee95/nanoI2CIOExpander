/**
* @file i2CMasterForTest.ino
* @author J.SORANZO
* @date 26/11/2018
* @copyright 2018 CC0
* @version 1.0
* @brief Un petit programme pour tester l'I2C io Expander

Il s'agit d'un outil de test du projet pas du projet en lui-même
*/
#include <Wire.h>
#include "SerialCommand.h"

void setup(){
    Wire.begin();

    Serial.begin(9600);
    SerialCommand::init();
      Serial.print("<I2C Tools for i2CIOSlaveExpander project ");
    // Print Status to Serial Line regardless of COMM_TYPE setting
    // so use can open Serial Monitor and check configurtion 
    Serial.print(ARDUINO_TYPE);
    Serial.print(": BUILD ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.print(__TIME__);
    Serial.print(">\n");
    
    String forDisplay = F("Available commands :\n");
    forDisplay += F("Write commande : <W I2CADD REG DATA>\n");
    forDisplay += F("Read command :  <R I2CADD REG>\n");
    forDisplay += F("Display satus : <s>\n");
    forDisplay += F("R and W commands are in upper case and s in lower.\n");
    INTERFACE.print( forDisplay);
    
}

void loop(){
    SerialCommand::process();
}