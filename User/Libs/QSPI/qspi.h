//
// Created by 14135 on 24-12-13.
//
#pragma once

#include "quadspi.h"

#ifdef __cplusplus

#define INIT_DAT_LEN (30)

typedef struct
{
    uint8_t cmd;
    uint8_t len;
    uint8_t data[INIT_DAT_LEN];
}init_line_t;

class QSPI {
public:
    QSPI() = default;
    explicit QSPI(QSPI_HandleTypeDef* hqspi);

    int sendCommand();
    int sendCommand(uint8_t cmd);
    int sendCommand(uint8_t cmd, uint8_t data);
    int sendCommand(uint8_t cmd, uint16_t data, uint16_t data2);
    int sendCommand(uint8_t cmd, uint8_t* data, uint8_t len);

    int sendCommandList(init_line_t* init_operations, uint8_t len);

    QSPI_HandleTypeDef* hqspi;
    QSPI_CommandTypeDef sCommand{};

private:
    HAL_StatusTypeDef QSPI_HAL_Command(QSPI_CommandTypeDef *cmd) const;
    HAL_StatusTypeDef QSPI_HAL_Transmit(uint8_t *pData) const;
};

#endif