/**
* @file nanoI2CexpSample.ino
@mainpage
* @author J.Soranzo
* @date 5/01/2019
* @copyright 2019 CC0
* @version git_versionning
* @brief A sample of how to use the project nanoI2CIOExpander

@section dependencies Lib dependencies

_tipsAutoGenArduinoList_addCarriageReturns

*/

/** @todo replace by <> version and move the files*/
#include "nanoI2CIOExpLib.h"
// #include <anoI2CIOExpLib.h>

CNanoI2CIOExpander ioexp;

void setup(){
   ioexp.begin(); 
}

void loop(){

}