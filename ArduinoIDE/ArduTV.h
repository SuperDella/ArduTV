/*
  ArduTV.h - Library for basic functions of the shield ArduTV.
  For information plese send Email to: progettoschede@gmail.com
  Ver. 1.0 02.02.2025
*/
#ifndef ArduTV_h
#define ArduTV_h

#include "Arduino.h"

#ifndef u16
    //typedef uint16_t u16;
    //typedef uint8_t u8;

    typedef short unsigned int u16;
    typedef uint8_t u8;
#endif

class ArduTV
{
  public:
    ArduTV(int CSpin);
    void begin();
    unsigned int SendSingle(unsigned int VALUE);
    void PenColor(u8 red,u8 green,u8 blu);//valori ammessi: da 0 a 31!
    void PenColorDir(u16 color);
    void Clear(void);
    void Point(u16 CoordinateX,u16 CoordinateY);
    void PointDir(u16 CoordinateX,u16 CoordinateY,u16 Color);
    void Rect(u16 CoordinateX,u16 CoordinateY,u16 Larghezza,u16 Altezza,u16 fill);
    void Circle(u16 CoordinateX,u16 CoordinateY,u16 Raggio);
    void bitmap(const uint8_t* data, int x, int y, int width, int height);
    //void text(const char* str, int x, int y);
    void printchar(const char str, int x, int y,u8 scale);
    void BGColor(u8 red,u8 green,u8 blu);
    void printString(const char* str, int x, int y,u8 scale);
    void changeFont(u8 ind, u8 font[8]);
  private:
    int _CSpin;
    u16 _BGcolor;
};

#endif