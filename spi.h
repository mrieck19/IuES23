#include "tft.h"

#ifndef __SPI_H_
#define __SPI_H_

extern void TFT_Print(char* Text, U8 X, U8 Y, U8 Scale, U16 ForeColor, U16 BackColor, U8 Display_Orientation);

extern void SendCommandSeq(const uint16_t * data, uint16_t Anzahl);

extern void SPISend8Bit(uint8_t data);

extern void SPI_init();
extern void Display_init(void);
extern void resetDisplay();


#endif
