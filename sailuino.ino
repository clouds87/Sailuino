///////////////////////////////////////////////////////////////////////////////
// Project      : Sailuino
// Module       : Arduino firmware for Sailuino
// Language     : Arduino (C/C++)
//
// Filename     : sailuino.ino
//
// Created by   : Lorenzo Columbo
// Created at   : 20.05.18
// Version      : 1.1
//
// ++
// Description  : Arduino firmware for Sailuino
//                See associated header file for more information.
// ++
///////////////////////////////////////////////////////////////////////////////

#include "sailuino.hpp"

SoftwareSerial bt_uart = SoftwareSerial(BT_RX_PIN, BT_TX_PIN);
Servo          ru_srv;
Servo          ms_srv;

int ru_srv_pos;
int ms_srv_pos;

void setup()
{

  Serial.begin(9600);

  pinMode(BT_RX_PIN, INPUT);
  pinMode(BT_TX_PIN, OUTPUT);
  bt_uart.begin(9600);

  ru_srv.attach(RU_SRV_PIN);
  ms_srv.attach(MS_SRV_PIN);

  ru_srv_pos = SRV_MED_POS;
  ms_srv_pos = SRV_MED_POS;
}

void loop()
{
  char cmd = 0;

  // If there's any data on the bluetooth serial buffer, show them on the Serial Monitor
  while (bt_uart.available() > 0) {
    cmd = bt_uart.read();
  }
  
  switch(cmd) {
  case('L'):
    if (ru_srv_pos > SRV_MIN_POS) {
      ru_srv_pos = ru_srv_pos - SRV_DELTA_POS;
      ru_srv.write(ru_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => RU: ");
      Serial.println(ru_srv_pos);
    }
  break;
  case('M'):
    ru_srv_pos = SRV_MED_POS;
    ru_srv.write(ru_srv_pos);
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => RU: ");
    Serial.println(ru_srv_pos);
  break;
  case('R'):
    if (ru_srv_pos < SRV_MAX_POS) {
      ru_srv_pos = ru_srv_pos + SRV_DELTA_POS;
      ru_srv.write(ru_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => RU: ");
      Serial.println(ru_srv_pos);
    }
  break;
  case('A'):
    if (ms_srv_pos > SRV_MIN_POS) {
      ms_srv_pos = ms_srv_pos - SRV_DELTA_POS;
      ms_srv.write(ms_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => MS: ");
      Serial.println(ms_srv_pos);
    }
  break;
  case('B'):
    ms_srv_pos = SRV_MED_POS;
    ms_srv.write(ms_srv_pos);
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => MS: ");
    Serial.println(ms_srv_pos);
  break;
  case('C'):
    if (ms_srv_pos < SRV_MAX_POS) {
      ms_srv_pos = ms_srv_pos + SRV_DELTA_POS;
      ms_srv.write(ms_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => MS: ");
      Serial.println(ms_srv_pos);
    }
  break;
  default:
  break;
  }

}
