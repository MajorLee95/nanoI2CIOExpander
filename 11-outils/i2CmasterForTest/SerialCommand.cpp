/**********************************************************************

SerialCommand.h
COPYRIGHT (c) 2013-2015 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

// DCC++ BASE STATION COMMUNICATES VIA THE SERIAL PORT USING SINGLE-CHARACTER TEXT COMMANDS
// WITH OPTIONAL PARAMTERS, AND BRACKETED BY < AND > SYMBOLS.  SPACES BETWEEN PARAMETERS
// ARE REQUIRED.  SPACES ANYWHERE ELSE ARE IGNORED.  A SPACE BETWEEN THE SINGLE-CHARACTER
// COMMAND AND THE FIRST PARAMETER IS ALSO NOT REQUIRED.

// See SerialCommand::parse() below for defined text commands.

#include "SerialCommand.h"
#include <Wire.h>



extern int __heap_start, *__brkval;


///////////////////////////////////////////////////////////////////////////////

char SerialCommand::commandString[MAX_COMMAND_LENGTH+1];
// volatile RegisterList *SerialCommand::mRegs;
// volatile RegisterList *SerialCommand::pRegs;
// CurrentMonitor *SerialCommand::mMonitor;

///////////////////////////////////////////////////////////////////////////////



void SerialCommand::init(){

  sprintf(commandString,"");
} // SerialCommand:SerialCommand

///////////////////////////////////////////////////////////////////////////////

void SerialCommand::process(){
  char c;
    
  #if COMM_TYPE == 0

    while(INTERFACE.available()>0){    // while there is data on the serial line
        c=INTERFACE.read();
        if(c=='<')                    // start of new command
            sprintf(commandString,"");
        else if(c=='>')               // end of new command
           parse(commandString);                    
        else if(strlen(commandString)<MAX_COMMAND_LENGTH)
        // if comandString still has space, append character
        //just read from serial line
           sprintf(commandString,"%s%c",commandString,c);     // otherwise, character is ignored (but continue to look for '<' or '>')
    } // while
  
  #elif COMM_TYPE == 1

    EthernetClient client=INTERFACE.available();

    if(client){
      while(client.connected() && client.available()){        // while there is data on the network
      c=client.read();
      if(c=='<')                    // start of new command
        sprintf(commandString,"");
      else if(c=='>')               // end of new command
        parse(commandString);                    
      else if(strlen(commandString)<MAX_COMMAND_LENGTH)    // if comandString still has space, append character just read from network
        sprintf(commandString,"%s%c",commandString,c);     // otherwise, character is ignored (but continue to look for '<' or '>')
      } // while
    }

  #endif

} // SerialCommand:process
   
///////////////////////////////////////////////////////////////////////////////

void SerialCommand::parse(char *com){
    int address, reg, data; 
    String forDisplay = "";  
    switch(com[0]){
    case 'W': 
        // trame.send();
		if (sscanf(com+1,"%X %X %X",&address, &reg, &data) != 3) {
            INTERFACE.println("<X>");
            return;
        }
        forDisplay = F("<W @0x");
        forDisplay += String(address, HEX);
        forDisplay += " reg : 0x" + String(reg, HEX);
        forDisplay += " data : 0x" + String(data, HEX) + ">\n";
		INTERFACE.print( forDisplay );
		Wire.beginTransmission(address); // transmit to device #8
		// Wire.write("x is ");        // sends five bytes
        Wire.write(reg); 
		Wire.write(data);              // sends one byte
		Wire.endTransmission();    // stop transmitting
        
        break;
    case 'R':   //!< R commande for reading
        // trame.continusSwitch = ON;
        if ( sscanf(com+1,"%X %X",&address, &reg) != 2){
            INTERFACE.println("<X>");
            return;
        }
        Wire.beginTransmission(address);
        Wire.write(reg);
        Wire.endTransmission();
        Wire.requestFrom(address, 1);
        while (Wire.available()) data = Wire.read();
        forDisplay += "<R @0x" + String(address, HEX);
        forDisplay += " REG : 0x" + String(reg, HEX);
        forDisplay += " Data : 0x" + String(data, HEX); 
        forDisplay += ">\n";
		INTERFACE.print( forDisplay );
        break;
    case 'c':
        // trame.continusSwitch = OFF;
        INTERFACE.print("<c>\n");
        break;
    case 's':      // <s>
/*
 *    returns status messages containing track power status, throttle status, turn-out status, and a version number
 *    NOTE: this is very useful as a first command for an interface to send to this sketch in order to verify connectivity and update any GUI to reflect actual throttle and turn-out settings
 *    
 *    returns: series of status messages that can be read by an interface to determine status of DCC++ Base Station and important settings
 */
      INTERFACE.print("<I2C Tools for i2CIOSlaveExpander project ");
      INTERFACE.print(ARDUINO_TYPE);
      INTERFACE.print(": BUILD ");
      INTERFACE.print(__DATE__);
      INTERFACE.print(" ");
      INTERFACE.print(__TIME__);
      INTERFACE.print(">");

      INTERFACE.print("<COMM TYPE : ");
      // INTERFACE.print(COMM_TYPE);
      // INTERFACE.print(": ");

      #if COMM_TYPE == 0
        INTERFACE.print("SERIAL>\n");
      #elif COMM_TYPE == 1
        INTERFACE.print(Ethernet.localIP());
        INTERFACE.print(">\n");
      #endif
  
      break;        


/***** PRINT CARRIAGE RETURN IN SERIAL MONITOR WINDOW  ****/    
                
    case ' ':     // < >                
      INTERFACE.println("");
      break;  



            




  } // switch
}; // SerialCommand::parse

///////////////////////////////////////////////////////////////////////////////


