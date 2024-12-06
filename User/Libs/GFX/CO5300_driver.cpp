////
//// Created by 14135 on 24-12-5.
////
//
#include <cstdio>
#include "CO5300_driver.h"
#include "quadspi.h"

CO5300::CO5300() {

}

void sendCommand(init_line_t command) {
    if(command.cmd == 0){
        HAL_Delay(command.data[0]);
    }
    else{
        QSPI_CommandTypeDef sCommand;
        sCommand.Instruction = 0x02;
//        sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
        sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
        sCommand.Address = command.cmd << 8;
        if(command.len){
            sCommand.DataMode = QSPI_ADDRESS_4_LINES;
            sCommand.NbData = command.len;
            sCommand.DummyCycles = 0;
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
            if(HAL_QSPI_Command(&hqspi, &sCommand, 0xFF) != HAL_OK){
                printf("Command failed\n");
            }
            if(HAL_QSPI_Transmit(&hqspi, command.data, 0xFF) != HAL_OK){
                printf("Transmit failed\n");
            }

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        } else{
            sCommand.DataMode = QSPI_DATA_NONE;
            sCommand.DummyCycles = 0;
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
            if(HAL_QSPI_Command(&hqspi, &sCommand, 0xFF) != HAL_OK){
                printf("0 Command failed\n");
            }
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//            HAL_QSPI_Transmit_IT(&hqspi, command.data);
        }
    }
}

init_line_t init_operations[] = {
        {CO5300_C_SLPOUT, 0, {0}},
        {0x00, 1, {CO5300_SLPOUT_DELAY}},
        {0xFE, 1, {0}},
        {CO5300_W_SPIMODECTL, 1, {0x80}},
        {CO5300_W_PIXFMT, 1, {0x55}},
        {CO5300_W_WCTRLD1, 1, {0x20}},
        {CO5300_W_WDBRIGHTNESSVALHBM, 1, {0xFF}},
        {CO5300_C_DISPON, 0, {0}},
        {CO5300_W_WDBRIGHTNESSVALNOR, 1, {0xD0}},
        {CO5300_W_WCE, 1, {0x00}},
        {0, 1, {10}}
};

void CO5300::init() {
    // Initialize the QSPI
    for(const auto & init_operation : init_operations){
        sendCommand(init_operation);
    }
    sendCommand({CO5300_C_ALLPON, 0, {0}});
}