/*! \file SerialCommand.h
 * \copyright 2013-2015 
   \brief Part of DCC++ BASE STATION for the Arduino adapted to
 * \author Gregg E. Berman
 * \author J.SORANZO (only for adaptations)
 **********************************************************************

 
 
 * Part of DCC++ BASE STATION for the Arduino
 *********************************************************************
 * reused for :
 * all command are suppressed from DCC++
 
 * New command :
 
< W > for write
 
return < W >
 
< R > for read

return < R >

< s > for station status and COM connections

return see in the code for all informations.
 */

#ifndef SerialCommand_h
#define SerialCommand_h
#define INTERFACE Serial
#define ARDUINO_TYPE    "MEGA"

// #include "PacketRegister.h"
// #include "CurrentMonitor.h"


//VoLAB add - 2018:07
#include <Arduino.h>
// #include "Config.h"

#define  MAX_COMMAND_LENGTH         30

struct SerialCommand{
  static char commandString[MAX_COMMAND_LENGTH+1];
  //static volatile RegisterList *mRegs, *pRegs;
  //static CurrentMonitor *mMonitor;
  // static void init(volatile RegisterList *, volatile RegisterList *, CurrentMonitor *);
  static void init();
  static void parse(char *);
  static void process();
}; // SerialCommand
  
#endif




