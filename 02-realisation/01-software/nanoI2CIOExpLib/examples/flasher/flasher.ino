/**
* @file flasher.ino
* @author J.Soranzo
* @date 5/01/2019
* @copyright 2019 CC0
* @version git_versionning
* @brief A sample of how to use the CFlasherNanoExp class of the project nanoI2CIOExpander
*/

#include <anoI2CIOExpLib.h>


CFlasherNanoExp flashingLed;

void setup(){
    Serial.begin(9600);
    Serial.println( "Nano I2C IO Flasher sample start.");

    flashingLed.begin( 1, 100, 500, 4, 5000 );
    // flashingLed.reverseMode();  
}

void loop(){
    flashingLed.update();
    
}