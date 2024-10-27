/*
  ArdHDMI.cpp - Library for basic functions of the shield ArdHDMI.
  For information please send Email to: progettoschede@gmail.com
   Ver. 1.0 04.08.2024
*/

#include "Arduino.h"
#include "ArduTV.h"
#include "SPI.h"
#include "SPI.h"
//#include "Font.h"
//#include "Font_5x7.c"

ArduTV::ArduTV(int CSpin)
{
  _BGcolor=65535;
  _CSpin = CSpin;
  
}

void ArduTV::begin()
{
  pinMode(_CSpin, OUTPUT);
  digitalWrite(_CSpin, HIGH); 
  SPI.begin();         // initialize the SPI library
  //SPI.beginTransaction(SPISettings(750000, MSBFIRST, SPI_MODE0));
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

unsigned int ArduTV::SendSingle(unsigned int VALUE)
{
  unsigned int DATABACK;

  digitalWrite(_CSpin, LOW);
  DATABACK = SPI.transfer16(VALUE); 
  digitalWrite(_CSpin, HIGH);
  return DATABACK;
}

void ArduTV::PenColor(u8 red,u8 green,u8 blu)
{
	unsigned int RGB16=0;
	RGB16=red;
	RGB16=(RGB16<<5)+green;
	RGB16=(RGB16<<5)+blu;
  SendSingle(0x0001);
  SendSingle(RGB16);
  delay(1);
}

void ArduTV::BGColor(u8 red,u8 green,u8 blu)
{
	unsigned int RGB16=0;
	RGB16=red;
	RGB16=(RGB16<<5)+green;
	RGB16=(RGB16<<5)+blu;
    _BGcolor=RGB16;
  SendSingle(0x0008);
  SendSingle(RGB16);
  delay(1);
}

void ArduTV::PenColorDir(u16 color)
{ 
  SendSingle(0x0001);
  SendSingle(color);
  delay(1);
  
}

void ArduTV::Clear(void)
{
  SendSingle(0x0002);
  delay(150);

}

void ArduTV::Point(u16 CoordinateX,u16 CoordinateY)
{
  SendSingle(0x0003);
  SendSingle(CoordinateX);
  SendSingle(CoordinateY);
  delay(1);
 
}

void ArduTV::PointDir(u16 CoordinateX,u16 CoordinateY,u16 Color)
{
  SendSingle(0x0007);
  SendSingle(CoordinateX);
  SendSingle(CoordinateY);
  SendSingle(Color);
  //delay(1); 
  delayMicroseconds(400);
 
}

void ArduTV::Rect(u16 CoordinateX,u16 CoordinateY,u16 Larghezza,u16 Altezza,u16 fill)
{
  unsigned int DATABACK=0;

  SendSingle(0x0004);
  SendSingle(CoordinateX);
  SendSingle(CoordinateY);
  SendSingle(Larghezza);
  SendSingle(Altezza);
  SendSingle(fill);

  DATABACK=Larghezza*Altezza/600;
  delay(DATABACK+10);
  //delay(10);

}

void ArduTV::changeFont(u8 ind, u8 font[8])
{
  u16 font0,font1,font2,font3;

  font0 = font[1];
  font0 = font0<<8;
  font0 = font0+font[0];

  font1 = font[3];
  font1 = font1<<8;
  font1 = font1+font[2];

  font2 = font[5];
  font2 = font2<<8;
  font2 = font2+font[4];

  font3 = font[7];
  font3 = font3<<8;
  font3 = font3+font[6];

  SendSingle(0x0009);
  SendSingle(ind);
  SendSingle(font0);
  SendSingle(font1);
  SendSingle(font2);
  SendSingle(font3);

  delay(1);

}

void ArduTV::Circle(u16 CoordinateX,u16 CoordinateY,u16 Raggio)
{
  //unsigned int DATABACK=0;

  SendSingle(0x0005);
  SendSingle(CoordinateX);
  SendSingle(CoordinateY);
  SendSingle(Raggio);

 // DATABACK=Raggio/10;
  delay(20);
  //delay(10);
}


void ArduTV::bitmap(const uint8_t* data, int x, int y, int width, int height)
{

  if ((data == NULL) || ((x + width) < 0) || ((y + height) < 0) || (x > 640) || (y > 480)) 
  {
    // offscreen
    return;
  }

  for (int j = 0; j < height; j++) 
  {
    uint8_t b = data[j];

    for (int i = 0; i < width; i++) 
    {
      if (b & (1 << (7 - i))) 
      {
        Point(x + i, y + j);
        //set(x + i, y + j, _strokeR, _strokeG, _strokeB);
      } else {
          PointDir(x + i, y + j,_BGcolor);
       // set(x + i, y + j, _backgroundR, _backgroundG, _backgroundB); NO BACGROUND !!!
      }
    }
  }
}
/*
void ArdHDMI::text(const char* str, int x, int y)
{

  while (*str) {
    uint8_t const c = (uint8_t)*str++;

    if (c == '\n') {
      //y += _font->height;
      y += Font_5x7.height; //heigh of the font
    } else if (c == '\r') {
      x = 0;
    } else if (c == 0xc2 || c == 0xc3) {
      // drop
    } else {
      const uint8_t* b = Font_5x7.data[c];

      if (b == NULL) {
        b =  Font_5x7.data[0x20];
      }

      if (b) {
        bitmap(b, x, y, Font_5x7.width, Font_5x7.height);//font 5x7
      }

      //x += _font->width;
      x += Font_5x7.width;
    }
  }
}
*/

 void ArduTV::printchar(const char str, int x, int y,u8 scale)
 {
         uint8_t const c = str;
         if (c == '\n') 
         {
            y += (8*scale); //heigh of the font
         }
         else if (c == '\r')
         {
            x = 0;
         }
         SendSingle(0x0006);    
         SendSingle(x);
         SendSingle(y);
         SendSingle(c);
         SendSingle(scale);
         delay(2);
    
     }

     void ArduTV::printString(const char* str, int x, int y,u8 scale)
 {
     while (*str) 
     {
         uint8_t const c = (uint8_t)*str++;
         if (c == '\n') 
         {
            y += (8*scale); //heigh of the font
         }
         else if (c == '\r')
         {
            x = 0;
         }
         SendSingle(0x0006);    
         SendSingle(x);
         SendSingle(y);
         SendSingle(c);
         SendSingle(scale);
         delay(2);
         x +=(8*scale);
        

     }
 }
     
 