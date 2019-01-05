/**
* @file analogRead.ino
* @author J.Soranzo
* @date 5/01/2019
* @copyright 2019 CC0
* @version git_versionning
* @brief A analogRead to show of how to use the project nanoI2CIOExpander
*/

#include <anoI2CIOExpLib.h>

CNanoI2CIOExpander ioexp;

void setup(){
    Serial.begin(9600);
    Serial.println( "Nano I2C IO Expander sample start.");
    ioexp.begin();
    Serial.println( "Init = " + String(CNanoI2CIOExpander::initOk?"ok":"ko") );
    ioexp.test();

}
#define QUANTUM 5.0/1024.0
#define ERROR 0.1059 //need to be adjsuted 11% between 0.2 and 4.5V
void loop(){
    int analogVal;
    float voltage;
    analogVal = ioexp.analogRead( 0 );
    Serial.print( "analog value = " + String(analogVal) );
    voltage = (float)analogVal*QUANTUM*(1-ERROR);
    // voltage = (float)analogVal*QUANTUM;
    // voltage = QUANTUM;
    Serial.println( ", analog voltage = " + String(voltage, 3) );
    delay( 500);   
}