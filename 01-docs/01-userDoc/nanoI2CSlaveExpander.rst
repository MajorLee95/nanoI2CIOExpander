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
#. Ecriture terminée : à tester

====================================
To do
====================================

See doxygen doc @todo directive

====================================
Outil de test
====================================

Développement de i2CMasterForTest.ino

dans :

050-nanoI2CSlaveExpander\projet\11-outils\i2CMasterForTest

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