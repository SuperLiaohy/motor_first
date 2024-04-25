//
// Created by 24106 on 2023/11/29.
//

#include "Inc/oled.h"
#include "stm32f1xx_hal.h"
#include "Inc/OLED_Font.h"


#define OLED_W_SCL(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)(x))
#define OLED_W_SDA(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)(x))


void OLED_I2C_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

/**
  * @brief  I2Cå¼?å§?
  * @param  ??
  * @retval ??
  */
void OLED_I2C_Start(void)
{
    OLED_W_SDA(1);
    OLED_W_SCL(1);
    OLED_W_SDA(0);
    OLED_W_SCL(0);
}

/**
  * @brief  I2C???
  * @param  ??
  * @retval ??
  */
void OLED_I2C_Stop(void)
{
    OLED_W_SDA(0);
    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

/**
  * @brief  I2C?????ä¸????
  * @param  Byte è¦?????ä¸?ä¸????
  * @retval ??
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        OLED_W_SDA(Byte & (0x80 >> i));
        OLED_W_SCL(1);
        OLED_W_SCL(0);
    }
    OLED_W_SCL(1);	//é¢?????ä¸?????ä¸?????ç­?¿¡??
    OLED_W_SCL(0);
}

/**
  * @brief  OLED???ä»?
  * @param  Command è¦???¥ç??½ä»¤
  * @retval ??
  */
void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);		//ä»???°å?
    OLED_I2C_SendByte(0x00);		//???ä»?
    OLED_I2C_SendByte(Command);
    OLED_I2C_Stop();
}

/**
  * @brief  OLED?????
  * @param  Data è¦???¥ç??°æ?
  * @retval ??
  */
void OLED_WriteData(uint8_t Data)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);		//ä»???°å?
    OLED_I2C_SendByte(0x40);		//?????
    OLED_I2C_SendByte(Data);
    OLED_I2C_Stop();
}

/**
  * @brief  OLEDè®¾ç½®???ä½?½®
  * @param  Y ä»¥å·¦ä¸??ä¸ºå??¹ï?????¹å??????????ï¼?~7
  * @param  X ä»¥å·¦ä¸??ä¸ºå??¹ï?????¹å??????????ï¼?~127
  * @retval ??
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);					//è®¾ç½®Yä½?½®
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//è®¾ç½®Xä½?½®é«?ä½?
    OLED_WriteCommand(0x00 | (X & 0x0F));			//è®¾ç½®Xä½?½®ä½?ä½?
}

/*Ö¸¶¨µãµãÁÁ*/
void OLED_Point(uint8_t map[][128],uint8_t map_obj[][128]){
    uint8_t v;
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 8; ++j) {
            OLED_SetCursor(j,i);

            OLED_I2C_Start();
            OLED_I2C_SendByte(0x78);		//´Ó»úµØÖ·
            OLED_I2C_SendByte(0x40);		//Ð´Êý¾Ý
            for (int k = 0; k < 8; ++k) {
                v=(map[(j+1)*8-k-1][i] | map_obj[(j+1)*8-k-1][i]);
                OLED_W_SDA(v);
                OLED_W_SCL(1);
                OLED_W_SCL(0);
            }
            OLED_W_SCL(1);	//¶îÍâµÄÒ»¸öÊ±ÖÓ£¬²»´¦ÀíÓ¦´ðÐÅºÅ
            OLED_W_SCL(0);
            OLED_I2C_Stop();
        }
    }
}



void OLED_nclear(uint8_t Y){
    OLED_SetCursor((Y-1)*2, 0);
    for(uint8_t i = 0; i < 128; i++)
    {
        OLED_WriteData(0x00);
    }
    OLED_SetCursor((Y-1)*2+1, 0);
    for(uint8_t i = 0; i < 128; i++)
    {
        OLED_WriteData(0x00);
    }
}




/**
  * @brief  OLEDæ¸??
  * @param  ??
  * @retval ??
  */
void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for(i = 0; i < 128; i++)
        {
            OLED_WriteData(0x00);
        }
    }
}

/**
  * @brief  OLED?¾ç¤ºä¸?ä¸??ç¬?
  * @param  Line è¡??ç½?????ï¼?~4
  * @param  Column ???ç½?????ï¼?~16
  * @param  Char è¦??ç¤ºç?ä¸?ä¸??ç¬?????ï¼?SCII???å­??
  * @retval ??
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//è®¾ç½®???ä½?½®?¨ä??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//?¾ç¤ºä¸???¨å????
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//è®¾ç½®???ä½?½®?¨ä??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//?¾ç¤ºä¸???¨å????
    }
}

/**
  * @brief  OLED?¾ç¤ºå­??ä¸?
  * @param  Line èµ·å?è¡??ç½?????ï¼?~4
  * @param  Column èµ·å????ç½?????ï¼?~16
  * @param  String è¦??ç¤ºç?å­??ä¸²ï????ï¼?SCII???å­??
  * @retval ??
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
}
void OLED_ShowChar_0(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//è®¾ç½®???ä½?½®?¨ä??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(~OLED_F8x16[Char - ' '][i]);			//?¾ç¤ºä¸???¨å????
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//è®¾ç½®???ä½?½®?¨ä??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(~OLED_F8x16[Char - ' '][i + 8]);		//?¾ç¤ºä¸???¨å????
    }
}
void OLED_ShowString_0(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar_0(Line, Column + i, String[i]);
    }
    for ( ; i < 16; i++)
    {
        OLED_ShowChar_0(Line, Column + i, ' ');
    }

}





/**
  * @brief  OLEDæ¬¡æ??½æ?
  * @retval è¿???¼ç?äº???æ¬¡æ?
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  OLED?¾ç¤º?°å?ï¼??è¿??ï¼???°ï?
  * @param  Line èµ·å?è¡??ç½?????ï¼?~4
  * @param  Column èµ·å????ç½?????ï¼?~16
  * @param  Number è¦??ç¤ºç??°å?ï¼???´ï?0~4294967295
  * @param  Length è¦??ç¤ºæ?å­???¿åº¦ï¼???´ï?1~10
  * @retval ??
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  OLED?¾ç¤º?°å?ï¼??è¿??ï¼?¸¦ç¬???°ï?
  * @param  Line èµ·å?è¡??ç½?????ï¼?~4
  * @param  Column èµ·å????ç½?????ï¼?~16
  * @param  Number è¦??ç¤ºç??°å?ï¼???´ï?-2147483648~2147483647
  * @param  Length è¦??ç¤ºæ?å­???¿åº¦ï¼???´ï?1~10
  * @retval ??
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    uint8_t i;
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}






/**
  * @brief  OLED?¾ç¤º?°å?ï¼??????¶ï?æ­£æ?ï¼?
  * @param  Line èµ·å?è¡??ç½?????ï¼?~4
  * @param  Column èµ·å????ç½?????ï¼?~16
  * @param  Number è¦??ç¤ºç??°å?ï¼???´ï?0~0xFFFFFFFF
  * @param  Length è¦??ç¤ºæ?å­???¿åº¦ï¼???´ï?1~8
  * @retval ??
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + i, SingleNumber + '0');
        }
        else
        {
            OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
        }
    }
}

/**
  * @brief  OLED?¾ç¤º?°å?ï¼??è¿??ï¼???°ï?
  * @param  Line èµ·å?è¡??ç½?????ï¼?~4
  * @param  Column èµ·å????ç½?????ï¼?~16
  * @param  Number è¦??ç¤ºç??°å?ï¼???´ï?0~1111 1111 1111 1111
  * @param  Length è¦??ç¤ºæ?å­???¿åº¦ï¼???´ï?1~16
  * @retval ??
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
    }
}

/**
  * @brief  OLED?????
  * @param  ??
  * @retval ??
  */
void OLED_Init(void)
{
    uint32_t i, j;

    for (i = 0; i < 1000; i++)			//ä¸??å»¶æ?
    {
        for (j = 0; j < 1000; j++);
    }

    OLED_I2C_Init();			//ç«???????

    OLED_WriteCommand(0xAE);	//?³é??¾ç¤º

    OLED_WriteCommand(0xD5);	//è®¾ç½®?¾ç¤º?¶é????æ¯?????¨é???
    OLED_WriteCommand(0x80);

    OLED_WriteCommand(0xA8);	//è®¾ç½®å¤?·¯å¤????
    OLED_WriteCommand(0x3F);

    OLED_WriteCommand(0xD3);	//è®¾ç½®?¾ç¤º??§»
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0x40);	//è®¾ç½®?¾ç¤ºå¼?å§??

    OLED_WriteCommand(0xA1);	//è®¾ç½®å·???¹å?ï¼?xA1æ­£å¸¸ 0xA0å·????½®

    OLED_WriteCommand(0xC8);	//è®¾ç½®ä¸???¹å?ï¼?xC8æ­£å¸¸ 0xC0ä¸????½®

    OLED_WriteCommand(0xDA);	//è®¾ç½®COMå¼??ç¡?»¶??½®
    OLED_WriteCommand(0x12);

    OLED_WriteCommand(0x81);	//è®¾ç½®å¯¹æ?åº????
    OLED_WriteCommand(0xCF);

    OLED_WriteCommand(0xD9);	//è®¾ç½®é¢???µå???
    OLED_WriteCommand(0xF1);

    OLED_WriteCommand(0xDB);	//è®¾ç½®VCOMH??????çº§å?
    OLED_WriteCommand(0x30);

    OLED_WriteCommand(0xA4);	//è®¾ç½®?´ä¸ª?¾ç¤º???/?³é?

    OLED_WriteCommand(0xA6);	//è®¾ç½®æ­£å¸¸/??½¬?¾ç¤º

    OLED_WriteCommand(0x8D);	//è®¾ç½®???æ³?
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0xAF);	//å¼????ç¤?

    OLED_Clear();				//OLEDæ¸??
}