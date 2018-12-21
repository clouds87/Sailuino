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
Servo          bs_srv;

int ru_srv_pos;
int ms_srv_pos;
int bs_srv_pos;
void setup()
{

  Serial.begin(9600);

  pinMode(BT_RX_PIN, INPUT);
  pinMode(BT_TX_PIN, OUTPUT);
  bt_uart.begin(9600);

  ru_srv.attach(RU_SRV_PIN);
  ms_srv.attach(MS_SRV_PIN);
  bs_srv.attach(BS_SRV_PIN);
  
  reset();
}

void reset()
{
  ru_srv_pos = SRV_MED_POS;
  ms_srv_pos = SRV_MED_POS;
  bs_srv_pos = SRV_MED_POS;

  ru_srv.write(ru_srv_pos);
  delay(SRV_ACTION_DLY);

  ms_srv.write(ms_srv_pos);
  delay(SRV_ACTION_DLY);

  bs_srv.write(bs_srv_pos);
  delay(SRV_ACTION_DLY);
}
  
void loop()
{
  char cmd = 0;
    
  // If there's any data on the bluetooth serial buffer, show them on the Serial Monitor
  while (bt_uart.available() > 0) {
    cmd = bt_uart.read();
    Serial.print("bt_uart -> ");
    Serial.print(bt_uart.available());
    Serial.print("| cmd -> ");
    Serial.println(cmd);
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
  case('1'):
    if (bs_srv_pos < SRV_MIN_POS) {
      bs_srv_pos = bs_srv_pos + SRV_DELTA_POS;
      bs_srv.write(bs_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => BS: ");
      Serial.println(bs_srv_pos);
    }
  break;
  case('2'):
    bs_srv_pos = SRV_MED_POS;
    bs_srv.write(bs_srv_pos);
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => BS: ");
    Serial.println(bs_srv_pos);
  break; 
  case('3'):
    if (bs_srv_pos < SRV_MAX_POS) {
      bs_srv_pos = bs_srv_pos + SRV_DELTA_POS;
      bs_srv.write(bs_srv_pos);
      delay(SRV_ACTION_DLY);
      Serial.print(cmd);
      Serial.print(" => BS: ");
      Serial.println(bs_srv_pos);
    }
  break;
  case('P'):                      // andatura poppiera

    ms_srv_pos = SRV_MAX_POS;
    ms_srv.write(ms_srv_pos);     // randa a dritta
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => MS: ");
    Serial.println(ms_srv_pos); 
    
    bs_srv_pos = SRV_MIN_POS;
    bs_srv.write(bs_srv_pos);     // fiocco a sinistra
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => BS: ");
    Serial.println(bs_srv_pos);
    
    ru_srv_pos = SRV_MED_POS;
    ru_srv.write(ru_srv_pos);     // timone a centro
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => RU: ");
    Serial.println(ru_srv_pos);    
  break; 
   
  case('D'):                      // andatura con mura a dritta (al traverso)
    ms_srv_pos = SRV_MED_POS + 45;
    ms_srv.write(ms_srv_pos);     // randa a dritta con 45°
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => MS: ");
    Serial.println(ms_srv_pos);
  
    bs_srv_pos = SRV_MED_POS + 45;
    bs_srv.write(bs_srv_pos);     // idem per fiocco
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => BS: ");
    Serial.println(bs_srv_pos);
  break;  
  
   case('S'):                      // andatura con mura a SX (al traverso)
    ms_srv_pos = SRV_MAX_POS - 45;
    ms_srv.write(ms_srv_pos);     // randa a SX con 45°
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => MS: ");
    Serial.println(ms_srv_pos);
  
    bs_srv_pos = SRV_MAX_POS + 45;
    bs_srv.write(bs_srv_pos);     // idem per fiocco
    delay(SRV_ACTION_DLY);
    Serial.print(cmd);
    Serial.print(" => BS: ");
    Serial.println(bs_srv_pos);
  break; 
   
  case('X'):
	reset();
  break;  
  
  default:
  break;
  }

}
