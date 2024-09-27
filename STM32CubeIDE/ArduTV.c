/*
 * ArduTV.c
 *
 *  Created on: Jul 29, 2024
 *      Author: della
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

static uint16_t _BGcolor=65535;
extern SPI_HandleTypeDef hspi1;

uint16_t ATV_SendSingle(uint16_t VALUE)
{
  uint16_t DATABACK;

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
  DATABACK = HAL_SPI_Transmit(&hspi1,&VALUE,1,100);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
  return DATABACK;
}

void ATV_Point(uint16_t CoordinateX,uint16_t CoordinateY)
{
  ATV_SendSingle(0x0003);
  ATV_SendSingle(CoordinateX);
  ATV_SendSingle(CoordinateY);
  HAL_Delay(1);
}

void ATV_PenColor(uint8_t red,uint8_t green,uint8_t blu)
{
	uint16_t RGB16=0;
	RGB16=red;
	RGB16=(RGB16<<5)+green;
	RGB16=(RGB16<<5)+blu;
  ATV_SendSingle(0x0001);
  ATV_SendSingle(RGB16);
  HAL_Delay(1);
}

void ATV_BGColor(uint8_t red,uint8_t green,uint8_t blu)
{
	uint16_t RGB16=0;
	RGB16=red;
	RGB16=(RGB16<<5)+green;
	RGB16=(RGB16<<5)+blu;
    _BGcolor=RGB16;
  ATV_SendSingle(0x0008);
  ATV_SendSingle(RGB16);
  HAL_Delay(1);
}

void ATV_PenColorDir(uint16_t color)
{
  ATV_SendSingle(0x0001);
  ATV_SendSingle(color);
  HAL_Delay(1);
}

void ATV_Clear(void)
{
  ATV_SendSingle(0x0002);
  HAL_Delay(150);

}

void ATV_PointDir(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Color)
{
  ATV_SendSingle(0x0007);
  ATV_SendSingle(CoordinateX);
  ATV_SendSingle(CoordinateY);
  ATV_SendSingle(Color);
  HAL_Delay(1);

}

void ATV_Rect(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Larghezza,uint16_t Altezza,uint16_t fill)
{
	uint16_t DATABACK=0;

  ATV_SendSingle(0x0004);
  ATV_SendSingle(CoordinateX);
  ATV_SendSingle(CoordinateY);
  ATV_SendSingle(Larghezza);
  ATV_SendSingle(Altezza);
  ATV_SendSingle(fill);

  DATABACK=Larghezza*Altezza/600;
  //DATABACK=Larghezza*Altezza/999;
  HAL_Delay(DATABACK+10);
  //HAL_Delay(10);

}

void ATV_Circle(uint16_t CoordinateX,uint16_t CoordinateY,uint16_t Raggio)
{
  //unsigned int DATABACK=0;

  ATV_SendSingle(0x0005);
  ATV_SendSingle(CoordinateX);
  ATV_SendSingle(CoordinateY);
  ATV_SendSingle(Raggio);

 // DATABACK=Raggio/10;
  HAL_Delay(20);
  //delay(10);
}

void ATV_bitmap(const uint8_t* data, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

  if ((data == NULL) || ((x + width) < 0) || ((y + height) < 0) || (x > 640) || (y > 480))
  {
    // offscreen
    return;
  }

  for (uint16_t j = 0; j < height; j++)
  {
    uint8_t b = data[j];

    for (uint16_t i = 0; i < width; i++)
    {
      if (b & (1 << (7 - i)))
      {
        ATV_Point(x + i, y + j);
        //set(x + i, y + j, _strokeR, _strokeG, _strokeB);
      } else {
          ATV_PointDir(x + i, y + j,_BGcolor);
       // set(x + i, y + j, _backgroundR, _backgroundG, _backgroundB); NO BACGROUND !!!
      }
    }
  }
}

void ATV_printchar(const char str, uint16_t x, uint16_t y,uint8_t scale)
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
        ATV_SendSingle(0x0006);
        ATV_SendSingle(x);
        ATV_SendSingle(y);
        ATV_SendSingle(c);
        ATV_SendSingle(scale);
        HAL_Delay(2);
    }

void ATV_printString(const char* str, uint16_t x, uint16_t y,uint8_t scale)
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
    ATV_SendSingle(0x0006);
    ATV_SendSingle(x);
    ATV_SendSingle(y);
    ATV_SendSingle(c);
    ATV_SendSingle(scale);
    HAL_Delay(2);
    x +=(8*scale);

}
}
