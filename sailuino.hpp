///////////////////////////////////////////////////////////////////////////////
// Project      : Sailuino
// Module       : Arduino firmware for Sailuino
// Language     : Arduino (C/C++)
//
// Filename     : sailuino.ino
//
// Created by   : Lorenzo Columbo
// Created at   : 20.05.18
// Version      : 1.0
//
// ++
// Description  : Arduino firmware for Sailuino
//                This application allows to open a Bluetooth connection to
//                provide, through a character-based interface, the control 
//                of all the servo motors of the Sailuino remotely controlled 
//                boat model.
// ++
///////////////////////////////////////////////////////////////////////////////

#ifndef SAILUINO_HPP_
#define SAILUINO_HPP_

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <Servo.h>

// Definition of some global constants and macros
#define BT_TX_PIN   12   // Bluetooth software serial Tx pin
#define BT_RX_PIN   13   // Bluetooth software serial Rx pin
#define RU_SRV_PIN   5   // Rudder servo control pin      // dal pin pwm 6 frecato
#define MS_SRV_PIN   3   // Main sail servo control pin
#define BS_SRV_PIN   9   // Bow sail servo control pin

const int SRV_MIN_POS    =    30;
const int SRV_MED_POS    =   90;
const int SRV_MAX_POS    =  180;
const int SRV_DELTA_POS  =   15;
const int SRV_ACTION_DLY = 1000;

void(* resetFunc) (void) = 0;

#endif /* SAILUINO_HPP_ */
