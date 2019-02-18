/**
* @file blink.ino
* @author J.Soranzo
* @date 5/01/2019
* @copyright 2019 CC0
* @version git_versionning
* @brief A little blink on output n°8 of how to use the project nanoI2CIOExpander
*/


#include <nanoI2CIOExpLib.h>


CNanoI2CIOExpander ioexp;

void setup(){
    Serial.begin(9600);
    Serial.println( "Nano I2C IO Expander Blink sample start.");
    ioexp.begin();
    Serial.println( "Init = " + String(CNanoI2CIOExpander::initOk?"ok":"ko") );
    ioexp.test();
    ioexp.pinMode( 8, OUTPUT );
   
}

void loop(){
    ioexp.digitalWrite(8, HIGH);
    delay( 500);
    ioexp.digitalWrite(8, LOW);
    delay( 500);
    
}