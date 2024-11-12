/* 
 * kekse23.de RCUSB5 v1.1
 * Copyright (c) 2020, Nicholas Regitz
 * 
 * Diese Datei ist Lizensiert unter der Creative Commons 4.0 CC BY-NC-SA
 * https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *  Translated to Sl-SI from github.com/gbraad/arduino-RCUSB4 and added comments for revija TIM - Miha Kočar
 */

//potrebne njižnice
//https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>
//https://github.com/gbraad/arduino-RCUSB4/tree/master
#include "AVRPort23.h"

//fiksne konstante
#define Kanal_1 D,3 //Pin 3
#define Interupt_1 3

#define Kanal_2 D,2 //Pin 2
#define Interupt_2 2

#define Kanal_3 D,1 //Pin 1 X3-aux1
#define Interupt_3 1

#define Kanal_4 D,0 //Pin 0 
#define Interupt_4 0

#define Kanal_5 E,7 //Pin 6
#define Interupt_5 7

//spremenljivke za hrambo sprotnih podatkov
volatile unsigned long TrenutnaUra[5];
volatile unsigned int Value[5];
volatile bool ZaznanaSprememba[5];
unsigned int NovaVrednost[5];

//definicija katere funkcije bo imela naša igralna palica
Joystick_ USB_Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  0, 0,                   // Button Count, Hat Switch Count
  true, true, false,      // X, Y, Z
  true, true, true,       // Rx, Ry, Rz
  false, false,           // Rudder, Throttle
  false, false, false);   // Accelerator, Brake, Steering

//Kaj se naj zgodi takoj ob prklopu
void setup()
{
  //poskrbimo da so vsi potrebni kanali vhod in pulup uporanik na high
  portMode(Kanal_1, INPUT, HIGH);
  portMode(Kanal_2, INPUT, HIGH);
  portMode(Kanal_3, INPUT, HIGH);
  portMode(Kanal_4, INPUT, HIGH);
  portMode(Kanal_5, INPUT, HIGH);
  
  ///aktiviramo igralno palico ter nastavimo delovna območja
  USB_Joystick.begin();
  USB_Joystick.setXAxisRange(2250, 750);
  USB_Joystick.setYAxisRange(2250, 750);
  USB_Joystick.setRxAxisRange(2250, 750);
  USB_Joystick.setRyAxisRange(2250, 750);
  USB_Joystick.setRzAxisRange(2250, 750);
  
  //priklopimo interupte
  attachInterrupt(Interupt_1, Zaznal_1, CHANGE);
  attachInterrupt(Interupt_2, Zaznal_2, CHANGE);
  attachInterrupt(Interupt_3, Zaznal_3, CHANGE);
  attachInterrupt(Interupt_4, Zaznal_4, CHANGE);
  attachInterrupt(Interupt_5, Zaznal_5, CHANGE);
}


//to se izvaja vedno znova
void loop()
{   
  if (ZaznanaSprememba[0])
  {
    NovaVrednost[0] = (NovaVrednost[0]+Value[0])/2;
    USB_Joystick.setXAxis(NovaVrednost[0]);
    ZaznanaSprememba[0] = false;
  }

  if (ZaznanaSprememba[1])
  {
    NovaVrednost[1] = (NovaVrednost[1]+Value[1])/2;
    USB_Joystick.setYAxis(NovaVrednost[1]);
    ZaznanaSprememba[1] = false;
  }
  
   if (ZaznanaSprememba[2])
  {
    NovaVrednost[2] = (NovaVrednost[2]+Value[2])/2;
    USB_Joystick.setRxAxis(NovaVrednost[2]);
    ZaznanaSprememba[2] = false;
  }
  
   if (ZaznanaSprememba[3])
  {
    NovaVrednost[3] = (NovaVrednost[3]+Value[3])/2;
    USB_Joystick.setRyAxis(NovaVrednost[3]);
    ZaznanaSprememba[3] = false;
  }

   if (ZaznanaSprememba[4])
  {
    NovaVrednost[4] = (NovaVrednost[4]+Value[4])/2;
    USB_Joystick.setRzAxis(NovaVrednost[4]);
    ZaznanaSprememba[4] = false;
  }
  
  delay(1);
}

//kaj naj počnejo posamezni interupti

void Zaznal_1()
{
  if (portRead(Kanal_1)) TrenutnaUra[0] = micros();
  else if (micros() > TrenutnaUra[0])
  {
    Value[0] = (Value[0]+(micros()-TrenutnaUra[0]))/2;
    ZaznanaSprememba[0] = true;
  }
}

void Zaznal_2()
{
  if (portRead(Kanal_2)) TrenutnaUra[1] = micros();
  else if (micros() > TrenutnaUra[1])
  {
    Value[1] = (Value[1]+(micros()-TrenutnaUra[1]))/2;
    ZaznanaSprememba[1] = true;
  }
}

void Zaznal_3()
{
  if (portRead(Kanal_3)) TrenutnaUra[2] = micros();
  else if (micros() > TrenutnaUra[2])
  {
    Value[2] = (Value[2]+(micros()-TrenutnaUra[2]))/2;
    ZaznanaSprememba[2] = true;
  }
}

void Zaznal_4()
{
  if (portRead(Kanal_4)) TrenutnaUra[3] = micros();
  else if (micros() > TrenutnaUra[3])
  {
    Value[3] = (Value[3]+(micros()-TrenutnaUra[3]))/2;
    ZaznanaSprememba[3] = true;
  }
}

void Zaznal_5()
{
  if (portRead(Kanal_5)) TrenutnaUra[4] = micros();
  else if (micros() > TrenutnaUra[4])
  {
    Value[4] = (Value[4]+(micros()-TrenutnaUra[4]))/2;
    ZaznanaSprememba[4] = true;
  }
}
