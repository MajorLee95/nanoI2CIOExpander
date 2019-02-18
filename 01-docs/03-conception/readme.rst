++++++++++++++++++++++++++++++++++++++++
Conception de nanoI2CSlaveExpander
++++++++++++++++++++++++++++++++++++++++

.. contents:: Table of Contents
.. section-numbering::

.. include:: ../../README.rst
   :encoding: UTF-8
   
==============
Progretion
==============
#. I2C master tools (dossier test) for test : OK
#. I2C slave : réception testée : OK
#. Etudier ce qu'il se passe au niveau des requête lors d'une demande d'accès en lecture OK
#. Lecture / ecriture dans les registres : OK
#. Write ended : to be tested (analog and digital) Ok
#. Write ARDUINO lib for use Ok
#. Test ARDUINO lib with ESP8266 : ok
#. Write the documentation tree : ok
#. finish user manual (wiring Fritzing) ok

=================================
On feb 2019 possible evolutions
=================================
#. implement nano EEPROM acces through I2C bus (and creat lib objects and methodes) 
#. implement nano UART acces 
#. add 3 digital I/O for the ESP plug project (D10-D11-D12) component address chose with D13 limite
number of same components on the same bus to two. (ok in version 2)

====================================
ARDUINO lib
====================================

Once the nano is loaded with the project here, we need an ARDUINO lib to use it.

Creation of the lib dev dir in 
\projet\02-realisation\01-software

name : nanoI2CIOExpLib

Class name : CNanoI2CIOExpander 

Needed method:

- void begin( I2C_ADD default = 0x58 )
- void pinMode( pin = 0 to 10 )
- void digitalWrite( pin, STATE ) : STATE = LOW or HIGH, PIn 0 to 10
- int digitalRead( pin )
- int analogRead( A0 to A7 ) : warning there is diff with ARDUINO pin A0 to A3 and A7, A7
A4 A5 excluded return 0


==============================
Tips on Arduino lib creation
==============================
As #include doasen't support relative path and that the ARDUINO lib structure requires
to put examples file in the sub directory "examples", it is impossible to work on examples without
copying source lib files in the exampes directory. So for working on examples purpose I move 
the lib files in the examples directory and when the work is finished I move these files in the 
upper lib directory

==============================
Tests
==============================

Test program
====================================

dev of i2CMasterForTest.ino

in :

050-nanoI2CSlaveExpander\projet\11-outils\i2CMasterForTest

Passed tests
==================

R/W from to registers : ok

<R5f 5>

digital inputs : D3, D4 D5 D5 D6 D7 D8 D9

<W5F 7 fe>

inputs pullup : ok

digital outputs : D2(0) ok

analog input A0 75mV error on 1V and 218mV @2.5V, 326mV @4V

analog globaly tested but not fully A1 ok, A2 ok with about the same error

Address bits D10..D12 ok @58,59, 5C and 5e tested

====================================
To do
====================================

See doxygen doc @todo directive

============================
Base adresse
============================

Some other components adds, for information
============================================
- 24CXX 0x50
- DS3231 0x68 (décaler à droite d'un bit vs dts source RTCLib)
- PCF8574 0x20 et 0x30
- MPC23017 0x20
- INA219 0x40
- BME680 0x33
- MPU6050 0x68

Choosed add, in config.h
============================
0x5F base (selec bits on D12..D10) @1 by default

============================
Register MAP
============================

See Doxygen source documentation of MAXREG macro in the config.h file.

============================
Pining
============================

- D0-D1 :<=> RX-TX for download and debug
- D2..D9 : 8 digital IO
- D10..D12 : I2C low address bits (default 1 with internal pullup)
- D13 bultin LED
- A4-A5 I2C pin
- A0-A3 : 4 analog inputs
- A6-A7 : 2 analog inouts

================
V2 Pining
================

- D0-D1 :<=> RX-TX for download and debug
- D2..D9 : 8 digital IO
- D10..D12 : 3 more digital IOs with new registers
- D13 I2C address complement
- A4-A5 I2C pin
- A0-A3 : 4 analog inputs
- A6-A7 : 2 analog inouts

########

.. include:: ../../VoLAB.rst
   :encoding: UTF-8

=============
Webographie
=============

.. target-notes::