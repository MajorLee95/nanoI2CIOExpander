++++++++++++++++++++++++++++++++++++++++
Conception de nanoI2CSlaveExpander
++++++++++++++++++++++++++++++++++++++++

.. contents:: Table of Contents
.. section-numbering::

.. include:: ../../README.rst
   :encoding: UTF-8
   
==============
Avancement
==============
#. I2C master tools (dossier test) for test : OK
#. I2C slave : réception testée : OK
#. Etudier ce qu'il se passe au niveau des requête lors d'une demande d'accès en lecture OK
#. Lecture / ecriture dans les registres : OK
#. Write ended : to be tested (analog and digital)
#. Write ARDUINO lib for use

====================================
ARDUINO lib
====================================

Once the nano is loaded with the project here, we need an ARDUINO lib to use it.

Creation of the lib dev dir in 
\projet\02-realisation\01-software

name : nanoI2CIOExpLib

Class name : CNanoI2CIOExpander 

Needed method:

- void begin( I2C_ADD default = 0x5F )
- void pinMode( pin = 0 to 7 )
- void digitalWrite( pin, STATE ) : STATE = LOW or HIGH, PIn 0 to 7
- int digitalRead( pin )
- int analogRead( A0 to A7 ) : warning there is diff with ARDUINO pin A0 to A3 and A7, A7
A4 A5 excluded return 0

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

########

.. include:: ../../VoLAB.rst
   :encoding: UTF-8

=============
Webographie
=============

.. target-notes::