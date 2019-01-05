/**
 @file nanoI2CIOExpLib.h
 @author J.SORANZO
 @date 05/01/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Header file of the class CNanoI2CIOExpander...
 
 @details This file doesn't instanciate any instance of this class. It is the user job...
*/
#ifndef NANOI2CIOEXPANDER_H
#define NANOI2CIOEXPANDER_H




/**
* @class CNanoI2CIOExpander CNanoI2CIOExpander.h
* @brief A class to provide usual io functioon for nanoI2CIOExpander project...

Functions provided are begin, pinMode, digitalRead, digitalWrite, analogRead
*/
class CNanoI2CIOExpander{
    
 
public: 
    CNanoI2CIOExpander(){};
    void begin( int add = 0x5F );
    void pinMode();
    int digitalRead( int input );
    void digitalWrite( int output, int value );
    int analogRead( int input);
    
};

#endif