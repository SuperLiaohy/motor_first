//
// Created by 24106 on 2023/11/29.
//

#ifndef OLED_4_OLED_H
#define OLED_4_OLED_H
#include <stdio.h>
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

void OLED_Point(uint8_t map[][128],uint8_t map_obj[][128]);


void OLED_ShowString_0(uint8_t Line, uint8_t Column, char *String);
void OLED_nclear(uint8_t Y);


#endif //OLED_4_OLED_H