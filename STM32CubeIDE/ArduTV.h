/**
  ******************************************************************************
  * @file           : ArduTV.h
  * @brief          : Header for ArduTV.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 ArduTV.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef ArdHDMI_h
#define ArdHDMI_h


//typedef uint16_t u16;
//typedef uint16_t u8;
/*
class ArdHDMI
{
  public:
   */

    int _CSpin;


    //ArdHDMI(int CSpin);
    //void begin();
    uint16_t ATV_SendSingle(uint16_t VALUE);
    void ATV_PenColor(uint8_t red,uint8_t green,uint8_t blu);//valori ammessi: da 0 a 31!
    void ATV_PenColorDir(uint16_t color);
    void ATV_Clear(void);
    void ATV_Point(uint16_t CoordinateX,uint16_t CoordinateY);
    void ATV_PointDir(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Color);
    void ATV_Rect(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Larghezza,uint16_t Altezza,uint16_t fill);
    void ATV_Circle(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Raggio);
    void ATV_bitmap(const uint8_t* data, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    //void text(const char* str, int x, int y);
    void ATV_printchar(const char str, uint16_t x, uint16_t y,uint8_t scale);
    void ATV_BGColor(uint8_t red,uint8_t green,uint8_t blu);
    void ATV_printString(const char* str, uint16_t x, uint16_t y,uint8_t scale);
 // private:

//};

#endif
