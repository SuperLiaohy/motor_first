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
  * @brief  I2C�?�?
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
  * @brief  I2C?????�????
  * @param  Byte �?????�?�????
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
    OLED_W_SCL(1);	//�?????�?????�?????�?��??
    OLED_W_SCL(0);
}

/**
  * @brief  OLED???�?
  * @param  Command �???��??�令
  * @retval ??
  */
void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);		//�???��?
    OLED_I2C_SendByte(0x00);		//???�?
    OLED_I2C_SendByte(Command);
    OLED_I2C_Stop();
}

/**
  * @brief  OLED?????
  * @param  Data �???��??��?
  * @retval ??
  */
void OLED_WriteData(uint8_t Data)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);		//�???��?
    OLED_I2C_SendByte(0x40);		//?????
    OLED_I2C_SendByte(Data);
    OLED_I2C_Stop();
}

/**
  * @brief  OLED设置???�?��
  * @param  Y 以左�??为�??��?????��??????????�?~7
  * @param  X 以左�??为�??��?????��??????????�?~127
  * @retval ??
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);					//设置Y�?��
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X�?���?�?
    OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X�?���?�?
}

/*ָ�������*/
void OLED_Point(uint8_t map[][128],uint8_t map_obj[][128]){
    uint8_t v;
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 8; ++j) {
            OLED_SetCursor(j,i);

            OLED_I2C_Start();
            OLED_I2C_SendByte(0x78);		//�ӻ���ַ
            OLED_I2C_SendByte(0x40);		//д����
            for (int k = 0; k < 8; ++k) {
                v=(map[(j+1)*8-k-1][i] | map_obj[(j+1)*8-k-1][i]);
                OLED_W_SDA(v);
                OLED_W_SCL(1);
                OLED_W_SCL(0);
            }
            OLED_W_SCL(1);	//�����һ��ʱ�ӣ�������Ӧ���ź�
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
  * @brief  OLED�??
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
  * @brief  OLED?�示�?�??�?
  * @param  Line �??�?????�?~4
  * @param  Column ???�?????�?~16
  * @param  Char �??示�?�?�??�?????�?SCII???�??
  * @retval ??
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置???�?��?��??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//?�示�???��????
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置???�?��?��??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//?�示�???��????
    }
}

/**
  * @brief  OLED?�示�??�?
  * @param  Line 起�?�??�?????�?~4
  * @param  Column 起�????�?????�?~16
  * @param  String �??示�?�??串�????�?SCII???�??
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
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置???�?��?��??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(~OLED_F8x16[Char - ' '][i]);			//?�示�???��????
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置???�?��?��??????
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(~OLED_F8x16[Char - ' '][i + 8]);		//?�示�???��????
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
  * @brief  OLED次�??��?
  * @retval �???��?�???次�?
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
  * @brief  OLED?�示?��?�??�??�???��?
  * @param  Line 起�?�??�?????�?~4
  * @param  Column 起�????�?????�?~16
  * @param  Number �??示�??��?�???��?0~4294967295
  * @param  Length �??示�?�???�度�???��?1~10
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
  * @brief  OLED?�示?��?�??�??�?���???��?
  * @param  Line 起�?�??�?????�?~4
  * @param  Column 起�????�?????�?~16
  * @param  Number �??示�??��?�???��?-2147483648~2147483647
  * @param  Length �??示�?�???�度�???��?1~10
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
  * @brief  OLED?�示?��?�??????��?正�?�?
  * @param  Line 起�?�??�?????�?~4
  * @param  Column 起�????�?????�?~16
  * @param  Number �??示�??��?�???��?0~0xFFFFFFFF
  * @param  Length �??示�?�???�度�???��?1~8
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
  * @brief  OLED?�示?��?�??�??�???��?
  * @param  Line 起�?�??�?????�?~4
  * @param  Column 起�????�?????�?~16
  * @param  Number �??示�??��?�???��?0~1111 1111 1111 1111
  * @param  Length �??示�?�???�度�???��?1~16
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

    for (i = 0; i < 1000; i++)			//�??延�?
    {
        for (j = 0; j < 1000; j++);
    }

    OLED_I2C_Init();			//�???????

    OLED_WriteCommand(0xAE);	//?��??�示

    OLED_WriteCommand(0xD5);	//设置?�示?��????�?????��???
    OLED_WriteCommand(0x80);

    OLED_WriteCommand(0xA8);	//设置�?���????
    OLED_WriteCommand(0x3F);

    OLED_WriteCommand(0xD3);	//设置?�示??��
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0x40);	//设置?�示�?�??

    OLED_WriteCommand(0xA1);	//设置�???��?�?xA1正常 0xA0�????��

    OLED_WriteCommand(0xC8);	//设置�???��?�?xC8正常 0xC0�????��

    OLED_WriteCommand(0xDA);	//设置COM�??�?��??��
    OLED_WriteCommand(0x12);

    OLED_WriteCommand(0x81);	//设置对�?�????
    OLED_WriteCommand(0xCF);

    OLED_WriteCommand(0xD9);	//设置�???��???
    OLED_WriteCommand(0xF1);

    OLED_WriteCommand(0xDB);	//设置VCOMH??????级�?
    OLED_WriteCommand(0x30);

    OLED_WriteCommand(0xA4);	//设置?�个?�示???/?��?

    OLED_WriteCommand(0xA6);	//设置正常/??��?�示

    OLED_WriteCommand(0x8D);	//设置???�?
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0xAF);	//�????�?

    OLED_Clear();				//OLED�??
}