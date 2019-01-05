/**
* @file debugSerialPort.h
* @author J.SORANZO
* @date about september 2018
* @copyright 2018 CC0
* @version 1.0
* @brief all macros that i use tu print debug message on ARUDINO
*/

#ifndef DEBUGSERIALPORT_H
#define DEBUGSERIALPORT_H

/**
* @def DEBUG
Debug mode switch. If it is defined we are in debug mode

else we ar in no debug mode
*/
// #define DEBUG
//comment to pass in non debug mode

/**
* @def DEBUGPORT
The name of the serial port to display debug message
* @def DEBUGSPEED
the speed in bauds of the debug port
*/
#define DEBUGPORT Serial
#define DEBUGSPEED 9600

/**
* @def sp(X)
sp macro for Serial.print
* @def spl(X)
for Serial.println
*/
#define sp(X) DEBUGPORT.print(X)
#define spl(X) DEBUGPORT.println(X)

#ifdef DEBUG
#define DSP(X) sp(X)
#define DSPL(X) spl(X)
#define DSPF(X) sp(F(X))
#define DSPLF(X) spl(F(X))
#else
#define DSP(X)
#define DSPL(X)
#define DSPF(X)
#define DSPLF(X) 
#endif

#ifdef DEBUG
/**
* @def DEFDPROMPT(X)
* @brief define the dPrompt String variable

Define the dPrompt String. I use to display a prompt before debug message
This allow to know wher i am in the code.

Generaly i use it at the begining of the function that i want to debug
*/
#define DEFDPROMPT(X) String dPrompt = F("<Volab "); \
    dPrompt += X; dPrompt += F(" : > ");
#else
#define DEFDPROMPT(X) String dPrompt = "";
#endif    

#endif

