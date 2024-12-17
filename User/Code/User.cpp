//
// Created by 14135 on 24-12-6.
//

#include <cstdio>
#include "User.h"
#include "CO5300_driver.h"
//#include "cmsis_os2.h"

QSPI qspi = QSPI(&hqspi);
CO5300 co5300 = CO5300(&qspi, GPIOB, GPIO_PIN_0);


uint8_t zero[] = {0x00};
uint8_t fivefive[] = {0x55};
uint8_t twozero[] = {0x20};
uint8_t ff[] = {0xFF};

void qspi_111_cmd_write(uint8_t Cmd, unsigned char* Data, long int Size)
{
    QSPI_CommandTypeDef sCommand;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0x000000 | (Cmd << 8);
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = Size;

    if(Size)
    {
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }

        if(HAL_QSPI_Transmit(&hqspi, Data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }else{
        sCommand.NbData = 1;
        sCommand.Address = 0x0000 | (Cmd);
        sCommand.AddressSize = QSPI_ADDRESS_16_BITS;
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }

        if(HAL_QSPI_Transmit(&hqspi, zero, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }
}


void qspi_114_cmd_write(unsigned char Cmd, unsigned char* Data, long int Size)
{
    QSPI_CommandTypeDef sCommand;
    sCommand.Instruction = 0x32;
    sCommand.Address = 0x000000 | (Cmd << 8);
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 0;
    sCommand.NbData = Size;

    if(Size)
    {
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }
        if(HAL_QSPI_Transmit(&hqspi, Data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }else{
        sCommand.NbData = 1;
        sCommand.Address = 0x0000 | (Cmd);
        sCommand.AddressSize = QSPI_ADDRESS_16_BITS;
        sCommand.DataMode = QSPI_DATA_1_LINE;
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }

        if(HAL_QSPI_Transmit(&hqspi, zero, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }
}

void qspi_144_cmd_write(unsigned char Cmd, unsigned char* Data, long int Size)
{
    QSPI_CommandTypeDef sCommand;
    sCommand.Instruction = 0x12;
    sCommand.Address = 0x000000 | (Cmd << 8);
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 0;
    sCommand.NbData = Size;

    if(Size)
    {
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }

        if(HAL_QSPI_Transmit(&hqspi, Data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }else{
        sCommand.NbData = 1;
        sCommand.Address = 0x0000 | (Cmd);
        sCommand.AddressSize = QSPI_ADDRESS_16_BITS;
        if(HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Command Failed");
        }

        if(HAL_QSPI_Transmit(&hqspi, zero, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            //log_debug("HAL_QSPI_Transmit Failed");
        }
    }
}

#define COL	368
#define ROW	448

#define Buffer_Size (COL * ROW)
static uint8_t OLED_Buffer[Buffer_Size];

void AMOLED_Block_Write(int Xstart, int Xend, int Ystart, int Yend)
{
    uint8_t a[] = {(uint8_t)(Xstart>>8), (uint8_t)(Xstart&0xff), (uint8_t)(Xend>>8), (uint8_t)(Xend&0xff)};
    uint8_t b[] = {(uint8_t)(Ystart>>8), (uint8_t)(Ystart&0xff), (uint8_t)(Yend>>8), (uint8_t)(Yend&0xff)};
    qspi_111_cmd_write(0x2A, a, 4);
    qspi_111_cmd_write(0x2B, b, 4);
    //qspi_111_cmd_write(0x2C, 0, 0);
}

void AMOLED_Clear(long int color)
{

    AMOLED_Block_Write(0, COL - 1, 0, ROW - 1);//set AMOLED GRAM

    for(int i = 0; i < COL * ROW; i += 2)
    {
        OLED_Buffer[i] 	   = color>>8; //HIGH_8bits
        OLED_Buffer[i + 1] = color & 0xff;
    }

    qspi_114_cmd_write(0x2c, (unsigned char*)OLED_Buffer, Buffer_Size);//HIGH_8bits
    qspi_114_cmd_write(0x3c, (unsigned char*)OLED_Buffer, Buffer_Size);//LOW_8bits
}

void AMOLED_DrawPoint(int x,int y,long int frontcolor)//����-----PEN_COLOR:�˵����ɫ
{
    if(x>=COL)
        x=COL-1;
    if(y>=ROW)
        y=ROW-1;

    AMOLED_Block_Write(x,x,y,y);

    OLED_Buffer[0] 	   = frontcolor >> 8;
    OLED_Buffer[1]     = frontcolor & 0xff;

    qspi_114_cmd_write(0x2c, (unsigned char*)OLED_Buffer, 2);
    qspi_114_cmd_write(0x3c, (unsigned char*)OLED_Buffer, 2);
}


void setup() {
    printf("setup\n");

//
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//RESET---HIGH
//    HAL_Delay(1);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//RESET---LOW
//    HAL_Delay(10);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//RESET---HIGH
//    HAL_Delay(50);
//
//    qspi_111_cmd_write(0x11, zero, 1);
//    HAL_Delay(100);
//
////	qspi_111_cmd_write(0x44, (uint8_t[]){0x01, 0xBF}, 2);
////	qspi_111_cmd_write(0x35, (uint8_t[]){0x00}, 1);
//
//    qspi_111_cmd_write(0x3A, fivefive, 1);
//    qspi_111_cmd_write(0x53, twozero, 1);
//    HAL_Delay(1);
//    qspi_111_cmd_write(0x51, zero, 1);
//    HAL_Delay(1);
//    qspi_111_cmd_write(0x29, zero, 0);
//    HAL_Delay(1);
//    qspi_111_cmd_write(0x51, ff, 1);
//
//    AMOLED_Clear(0x0000);
//    HAL_Delay(10);



    co5300.init();
//    HAL_Delay(1);
//    co5300.display_on();
//    HAL_Delay(1);
    co5300.set_brightness(100);
}
uint8_t test[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
void loop() {
//    for(uint8_t i = 100; i < 255; i++){
//        HAL_Delay(200);
//        int state = co5300.set_brightness(i);
//        if(state != HAL_OK){
//            printf("set brightness failed, state: %d\n", state);
//        }
//    }
//    for(uint8_t i = 0; i < 400; i++){
//        for (int j = 0; j < 400; j++) {
//            co5300.draw_pixel888(i, j, 0x123456);
//        }
//    }
//    for(uint8_t i = 10; i < 160; i++){
//        for (int j = 10; j < 160; j++) {
//            AMOLED_DrawPoint(i, j, 0x00FFFF);
//        }
//    }
//    co5300.init();
//    qspi.sendData(test, 8);
//    HAL_QSPI_Transmit(&hqspi, test, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    for(uint8_t i = 10; i < 16; i++){
        for (int j = 10; j < 16; j++) {
            co5300.draw_pixel888(i, j, 0xF1F110);
        }
    }
    HAL_Delay(100);
}