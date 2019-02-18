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


#define MAJVER 0x00
#define REGTEST1 0x01
#define REGTEST2 0x02
#define REGTEST3 0x03 // 0x55 (RO)
#define DDR 0x04 // DDR (R/W) 1 for output, default 0
#define DR 0x05 // digital DATA (R/W) a write on input bit has no effect
#define MINVER 0x06 // Minor version (RO)
#define PULLUP 0x07 // puulup reg (R/W) : 1 pullup is enable, default = 0
#define DDR2 0x08
#define DR2 0x09
#define PULLUP2 0x0A

// 0x08 to 0x0F : reserved (read data 0xA5)


/**
* @class CNanoI2CIOExpander nanoI2CIOExpLib.h
* @brief A class to provide usual io functioon for nanoI2CIOExpander project...

Functions provided are begin, pinMode, digitalRead, digitalWrite, analogRead
*/
class CNanoI2CIOExpander{

    public: 
        CNanoI2CIOExpander(){};
        //begin can't be static because it uses registerRead().
        void begin( int add = 0x5F );
        void pinMode( int output, int mode );
        int digitalRead( int input );
        void digitalWrite( int output, int value );
        int analogRead( int input);
        static bool initOk;
        void test();

    private:
        int readRegister( int add );
        void writeRegister( int add, int val);
};

/**
* @class CFlasherNanoExp nanoI2CIOExpLib.h
* @brief a Class to flash a LED through nanoI2CIOExpander...
 @details
This class is for flashing led with no delay function call with diffrents ton and toff

In setup or elsewhere create a Flasher instance  i and call i.begin( pin, ton, toff )

Or begin( pin, ton, toff, repeat, period ) to flash n time in the period.

reverseMode() can be used to inverse on and off times.

They are no default values.

In a loop call i.update();

To return to led off and stop flashing you can call i.stop()

i.getChangeStateCpt() can be used to flash a certain number of times

 @todo allways on
*/
class CFlasherNanoExp{
    public:    
        CFlasherNanoExp(){}
        CFlasherNanoExp( int compAdd){ _componentAdd = compAdd; }
        void begin( int pin, unsigned long ton, unsigned long toff);
        void begin( int pin, unsigned long ton, unsigned long toff, int repeat, unsigned long period);
        void update();
        void reverseMode();
        int getChangeStateCpt(){ return _changeStateCpt; }/**< @brief to stop flashing after a certain number of times*/
        void stop();

    private:
        CNanoI2CIOExpander _ioexp;
        int _componentAdd = 0x5F;
        unsigned long _ton;
        unsigned long _toff;
        unsigned long _period = 0;
        int _repeat = 0;
        int _repeatCount = 0;
        int _pin;
        unsigned long _previousMillis;
        unsigned long _previousPeriod = 0;
        int _ledState ;
        unsigned long _changeStateCpt;
        int _offLevel = 0;
        int _onLevel = 1;
        // bool _reverse = false;
};

#endif