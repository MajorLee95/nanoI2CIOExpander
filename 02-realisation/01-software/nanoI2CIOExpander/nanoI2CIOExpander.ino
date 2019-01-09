/**
* @file nanoI2CIOExpander.ino
@mainpage
* @author J.Soranzo
* @date December 2018
* @copyright 2018 MIT
* @version see config.h
* @brief ARDUINO Nano as I2C  analog and digital IO expander 

@section Documentation

Give you additionnal 8 digital in/out and 6 analog inputs 

with a simple low cost ARDUINO nano

more with a MEAG2560 but not tested and not implemented

Very useful for ESP8266 with its only on analog input

I2C base address is in the config.h and completed by D12..D10 pin with internal pullup

Analog A4 and A5 on nano are reserved for I2C communications.

@section Exemples

Connect SCLK to SCLk on ESP8266 and SDATA to SDATA on ESP8266.

Don't forget to connect ground between the components.

@section dependencies Lib dependencies

_tipsAutoGenArduinoList_addCarriageReturns

* @todo Add MEGA2560 more fonctionnalities (more analog and digital IO)

*/

#include <Wire.h>
#include "debugSerialPort.h"
#include "config.h"

/**
* @var registers
* @brief Main registers bank. See config.h MAXREG macro for full mapping;
*/
byte registers[MAXREG];

/** 
@fn void setup()
@brief ARDUINO setup function
@return no return value and no parameters

Prepare i2c slave address

Set debug port speed if DEBUG is enabled in the config.handler

Display Startup screen with build i2c add

Register 2 i2c event functions

Initialize registers

Display initialized registers
*/
void setup(){
    int address = i2cBuildAddress();
    
    DEBUGPORT.begin( DEBUGSPEED );
    
    DEFDPROMPT( "IOExpander setup" );
    //display Startup message
    DSP( dPrompt + String(ARDUINO_TYPE) + F(" version : ") + MA_VERSION +"."+MI_VERSION  );
    DSP(F(" : BUILD "));
    DSPL( (String)__DATE__ + " " + (String)__TIME__ );
    DSPL( dPrompt + F("I2C adresse : ")+String(address, HEX) );
    Wire.begin( address );
    Wire.onReceive(receiveEvent); // register event
    Wire.onRequest(requestEvent); // register event

    regInit();
    registers[3] = 0x55;
    for ( int i = 0; i < MAXREG ; i++ ){
        DSPL( dPrompt + "registers[" + String(i,HEX) + "] = " + String( registers[i], HEX) );
    }
    
}

int octetsRec = 0; /**< @brief  number of i2C received bytes*/
int reg = 1;/**< @brief global variable to track the registers address  for i2c requests*/

/** 
@fn void loop()
@brief ARDUINO loop, cyclicly update analog registers and digital
@return no return and no input parameter

The cyclical update of the registers is not very fast.
We could do this in a better way

* @todo improve the speed by updating i/o in a better way.

*/
void loop(){
    DEFDPROMPT("Receiver");
    delay(100);
    if (octetsRec != 0){
        DSPL( dPrompt + "Bytes rec : " + (String)octetsRec );
        DSPL( dPrompt + "reg = " + String(reg, HEX));
        DSPL( dPrompt + "registers[reg] = " + String(registers[reg], HEX) );
        if ( reg == 8 ){
            DSPL( "( (registers[5] & (1 << i) ) >> i ) avec i = 1 vaut " + (String)( (registers[5] & (1 << 1) ) >> 1 ) );
        }
        octetsRec = 0;
    }
    updateDigitals();
    updateAnalogs();
}
/** 
@fn void receiveEvent(int howMany)
@brief i2c receiver handler
@param howMany : nomber of received bytes 
(dosen't work if there is a Serial.print in the handler)
@return nothing
*/
void receiveEvent(int howMany) {
    octetsRec = howMany;
    int data;
    // Si howMany = 2 => écriture;
    // Si howMany = 1 => lecture;
    // while (1 < Wire.available()) { // loop through all but the last
        // char c = Wire.read(); // receive byte as a character
        // Serial.print(c);         // print the character
    // }
    reg = Wire.read();
    /**
    * @todo check for wrong parameters number
    */
    if (howMany == 2) {
        data = Wire.read();
        switch ( reg ){ //write enabled registers
            case 1:
            case 2:
            case 4:
            case 5:
            case 7:
                registers[ reg ] = data;
                break;
        }
    }
}

/** 
@fn void requestEvent()
@brief I2C transmit handler for Read request
*/
void requestEvent() {
  Wire.write(registers[reg]); // respond with message of 6 bytes
  // as expected by master
}

/** 
@fn void regInit()
@brief initialisation of the register bank

Works on global registers array.
*/
void regInit(){
    
    //first init all to 0xA5
    for ( int i = 0; i < MAXREG ; i++ ) registers[i] = 0xA5;
    
    //individual special registers init;
    registers[0] = MA_VERSION;
    registers[6] = MI_VERSION;
    registers[1] = 0;
    registers[2] = 0;
    registers[3] = 0x55;
    registers[4] = 0;
    registers[7] = 0;
    registers[24] = 0xCA;
    registers[25] = 0xFE;
    registers[26] = 0xFE;
    registers[27] = 0xCA;
}

/** 
@fn int i2cBuildAddress()
@brief Build i2c slave address with base ored with D12..D10 pin state
@return the builded address
*/
int i2cBuildAddress(){
    int address = I2CADD ;
    pinMode( I2CHIGHADD, INPUT_PULLUP );
    pinMode( I2CMIDADD, INPUT_PULLUP );
    pinMode( I2CLOWADD, INPUT_PULLUP );
    
    address |= digitalRead( I2CHIGHADD ) << 2;
    address |= digitalRead( I2CMIDADD ) << 1;
    address |= digitalRead( I2CLOWADD );
    return address;
}
/** 
@fn void updateAnalogs()
@brief as its name tells us update analog registers with analog inputs values
@return nothing and no input parameters

Works on global registers arrays
*/
void updateAnalogs(){
    int data;
    for ( int i = 0; i < 8 ; i++ ){
        if ( i != 4 && i !=5 ){
            data = analogRead( 14+i ); //14 <=> A0
            registers[0x10 + i*2] = byte(data & 0xFF);
            registers[0x10 + i*2+1] = byte((data & 0xFF00) >> 8);            
        } 
    }

}

/** 
@fn void updateDigitals()
@brief update digital registers and digital outputs
@return nothing and no input parameters

Works on global registers arrays
*/
void updateDigitals(){
    byte directions = registers[4];
    byte pullups = registers[7];
    
    for ( int i = 0; i < 8 ; i++ ){
        if ( directions & (1 << i) ){ //output
            pinMode( i+2, OUTPUT );
            digitalWrite( i+2, ( ( registers[5] & (1 << i) ) >> i ) );
        } else {
            int mode = (pullups & (1 << i) )?INPUT_PULLUP:INPUT;
            pinMode( i+2, mode );
            bitWrite( registers[5], i, digitalRead( i+2) );
        }
    }
}