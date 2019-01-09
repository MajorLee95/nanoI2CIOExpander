/**
 @file nanoI2CIOExpLib.cpp
 @author J.SORANZO
 @date _date
 @copyright 2018 CC0
 @version git versionning
 @brief implementation file of the class CNanoI2CIOExpander
*/

#include <Arduino.h>
#include <Wire.h>
#include "nanoI2CIOExpLib.h"

#define NANOEXP_ADDRESS 0x5F

bool CNanoI2CIOExpander::initOk = false;

/** 
 @fn void CNanoI2CIOExpander::begin( int add = 0x5F )
 @brief function that start the I2C protocol with nanoI2CIOExpander
 @param add the I2C address of the componant...
 @return nothing
 
 The default address of the componant is 0x5F 
 Can be fixed from 0x58 to 0x5F with D12D10D11 pin of the Nano
 Adress pin are pulled-up to 5V (so no connect value is 1)
*/
void CNanoI2CIOExpander::begin( int add ){
    Wire.begin();
    Wire.beginTransmission(NANOEXP_ADDRESS);
    if ( Wire.endTransmission() ) return;
    if ( readRegister( REGTEST3 ) != 0x55 ) return;
    CNanoI2CIOExpander::initOk = true;
    return;
    
}

/** 
 @fn void CNanoI2CIOExpander::pinMode( int output, int mode)
 @brief A method to set the pinMode but...
 @param output from 0 to 7
 @param mode INPUT, OUTPUT or INPUT_PULLUP
 @return nothing
 
  @warning input number from 0 to 7 corresponding to D2 to D9 on the nano
*/
void CNanoI2CIOExpander::pinMode( int output, int mode){
    if ( output > 7 ) return;
    int DDRVal;
    int pullupVal;
    DDRVal = readRegister( DDR );
    pullupVal = readRegister( PULLUP );
    if ( mode == INPUT ) {
        bitClear( DDRVal, output );
        bitClear( pullupVal, output );
    } else if (mode == OUTPUT) bitSet( DDRVal, output );
    else if (mode == INPUT_PULLUP ){
        bitClear( DDRVal, output );
        bitSet( pullupVal, output ); 
    }
    writeRegister( DDR, DDRVal );
    writeRegister( PULLUP, pullupVal );
}

/** 
 @fn int CNanoI2CIOExpander::digitalRead( int input )
 @brief Well knonwn function digitalRead applie to nanoI2CIOExpander but...
 @param input the number of the input
 @return the read value

 @warning input number from 0 to 7 corresponding to D2 to D9 on the nano
*/
int CNanoI2CIOExpander::digitalRead( int input ){
    int DRVal = readRegister( DR );
    return (int)bitRead( DRVal, input );
}

void CNanoI2CIOExpander::digitalWrite( int output, int value ){
    int DRVal;
    DRVal = readRegister( DR );
    if (value) bitSet ( DRVal, output );
    else bitClear(DRVal, output);
    writeRegister( DR, DRVal );
    
}

/** 
 @fn int CNanoI2CIOExpander::analogRead( int input)
 @brief A method tha return 10bits value of one of the 6 analog inputs...
 @param input analog input number from 0 to 5
 @return read value

Warning : mapping of analog inputs on ARDUINO Nano:
- 0 A0
- 1 A1
- 2 A2
- 3 A3
- 4 A6
- 5 A7
*/ 
int CNanoI2CIOExpander::analogRead( int input){
    int lowAdd = 0;
    if (input > 5 || input <0 )return 0;
    switch ( input ){
        case 0: lowAdd = 0X10; break;
        case 1: lowAdd = 0X12; break;
        case 2: lowAdd = 0X14; break;
        case 3: lowAdd = 0X16; break;
        case 4: lowAdd = 0X1C; break;
        case 5: lowAdd = 0X1E; break;
    }
    lowAdd;
    return readRegister( lowAdd )+ 256*readRegister( lowAdd+1);
    
}

/** 
 @fn int CNanoI2CIOExpander::readRegister( int add )
 @brief Private method to read a 8 bits register in the NANO IO Expander
 @param add is the addresse of the register to be read
 @return the read value
*/
int CNanoI2CIOExpander::readRegister( int add ){
    Wire.beginTransmission(NANOEXP_ADDRESS);
    Wire.write((uint8_t)add);
    Wire.endTransmission();
    Wire.requestFrom( (uint8_t)NANOEXP_ADDRESS, (uint8_t)1 );
    return (int)Wire.read();   
}

/** 
 @fn void CNanoI2CIOExpander::writeRegister( int add, int val)
 @brief Private method to write a 8 bits register in the NANO IO Expander
 @param add the address of the register to be write
 @param val the value to be write
 @return nothing
*/
void CNanoI2CIOExpander::writeRegister( int add, int val){
    Wire.beginTransmission((uint8_t)NANOEXP_ADDRESS);
    Wire.write((uint8_t)add);
    Wire.write((uint8_t)val);
    Wire.endTransmission();
}

/** 
 @fn void CNanoI2CIOExpander::test()
 @brief A special test method that use 2 special register to write and read and display 
 on the Serial monitor results...
 @return no return value and no parameter
 
 first write 0x10 to register Test1 (reg add = 1)
 and write 0x12 to register Test2 (reg add = 2)
 and re-read the values and display them on Serial monitor
*/
void CNanoI2CIOExpander::test(){
    Serial.println( "Write 0x10 to 1");
    writeRegister(1, 0X10);
    Serial.println( "Write 0x12 to 2");
    writeRegister(2, 0X12);
    Serial.println( "Read of reg 1 = " + String( readRegister(1), HEX  ) );
    Serial.println( "Read of reg 2 = " + String( readRegister(2), HEX  ) );
}

/** 
 @fn void CFlasherNanoExp::begin( int pin, unsigned long ton, unsigned long toff)
 @brief to prepare Led Flashing...
 @param pin the pin number where the LED is connected (anode connection and cathod to ground) 0 to 7
 @param ton time during the LED is switched on in milliseconds
 @param toff time during the LED is switched off in milliseconds
 @return no return value
 This function puts pin in output mode and write it to 0 (low state ie off)
*/
void CFlasherNanoExp::begin( int pin, unsigned long ton, unsigned long toff){
    _pin = pin;
    _ton = ton;
    _toff = toff;
    _ioexp.begin( _componentAdd );
    _ioexp.pinMode( _pin, OUTPUT);
    _ledState = 0;
    _previousMillis = 0;
    _changeStateCpt = 0;
    _ioexp.digitalWrite( _pin, _ledState );
    // _reverse= false;
    _offLevel = 0;
    _onLevel = 1;  
    
}

/** 
 @fn void CFlasherNanoExp::begin( int pin, unsigned long ton, unsigned long toff,\
 int repeat, unsigned long period)
 @brief Method to start flasher in repeat mode...
 @param pin same as in the normal implementation of begin
 @param ton same as in the normal implementation of begin
 @param toff same as in the normal implementation of begin
 @param repeat number of repetitions
 @param period total period
 @return nothing

period shall be greter then repeat*( ton + toff )

and repeat shall be greater than 1
*/
void CFlasherNanoExp::begin( int pin, unsigned long ton, unsigned long toff,\
 int repeat, unsigned long period){
    if ( ( repeat * ( ton + toff) < period ) && repeat >= 2 ){
        _repeat = repeat;
        _repeatCount = 0;
        _period = period;
        _previousPeriod = millis();
        begin( pin, ton, toff );
    }

 }

/** 
@fn void CFlasherNanoExp::update()
@brief This function should be call periodicly
@return no param and no return value

Function check time with millis function and switch LED if necessary
*/
void CFlasherNanoExp::update(){
    // probably there is a best way to do this in more efficient codding style
    if ( _repeat ){ //repeat mode
        if ( _repeatCount < _repeat ){
            if ( (millis()-_previousMillis  > _ton) && (_ledState == _onLevel) ){
                _ledState = _offLevel;
                _previousMillis = millis();
                _ioexp.digitalWrite( _pin, _ledState );
                _changeStateCpt++;
                _repeatCount++;
            } else if ( (millis()-_previousMillis  > _toff) && (_ledState == _offLevel) ){
                _ledState = _onLevel ;       
                _previousMillis = millis();
                _ioexp.digitalWrite( _pin, _ledState );
                _changeStateCpt++; 
            } 
        } else if ( millis()-_previousPeriod > _period ){
            _previousPeriod = millis();
            _repeatCount = 0;
            _previousMillis = millis();
        }
        
    } else { //normal mode
        if ( (millis()-_previousMillis  > _ton) && (_ledState == _onLevel) ){
            _ledState = _offLevel;
            _previousMillis = millis();
            _ioexp.digitalWrite( _pin, _ledState );
            _changeStateCpt++;
        } else if ( (millis()-_previousMillis  > _toff) && (_ledState == _offLevel) ){
            _ledState = _onLevel ;       
            _previousMillis = millis();
            _ioexp.digitalWrite( _pin, _ledState );
            _changeStateCpt++;
        }    
    }   
}

/** 
@fn void CFlasherNanoExp::stop()
@brief this function stop LED 
@return no param and no return value

Warning this function doesn't no prevent update() to work (except that the pin is in input mode)
*/
void CFlasherNanoExp::stop(){
    _ioexp.digitalWrite( _pin, 0 );
    _ledState = 0;
    _ioexp.pinMode( _pin, INPUT );
    _changeStateCpt = 0;
    _repeat = 0;
    _repeatCount = 0;
    _period = 0;
    _previousPeriod = 0;
    // _reverse= false;
    _offLevel = 0;
    _onLevel = 1;    
}

/** 
 @fn void CFlasherNanoExp::reverseMode()
 @brief Reverse the mode when it should be off it is on and conversely
 @return no return value and no parameter

A second call return to normal state
*/
void CFlasherNanoExp::reverseMode(){
    int tmp;
    tmp = _offLevel;
    _offLevel = _onLevel;
    _onLevel = tmp;   

}