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

typedef enum
{
    BEGIN_WRITE,
    WRITE_COMMAND_8,
    WRITE_COMMAND_16,
    WRITE_DATA_8,
    WRITE_DATA_16,
    WRITE_BYTES,
    WRITE_C8_D8,
    WRITE_C8_D16,
    WRITE_C16_D16,
    END_WRITE,
    DELAY,
} spi_operation_type_t;

class QSPI {
public:
    QSPI() = default;
    explicit QSPI(QSPI_HandleTypeDef* hqspi);

    int sendCommand();
    int sendCommand(uint8_t cmd);
    int sendCommand(uint8_t cmd, uint8_t data);
    int sendCommand(uint8_t cmd, uint16_t data, uint16_t data2);
    int sendCommand(uint8_t cmd, uint8_t* data, uint8_t len);

    int sendData(uint8_t data);
    int sendData(uint8_t* data, uint8_t len);

    int sendCommandWithInstruction(uint8_t instruction, uint8_t cmd, uint8_t* data, uint8_t len);

    int sendCommandList(init_line_t* init_operations, uint8_t len);
    int sendCommandList2(const uint8_t *operations, size_t len);

    QSPI_HandleTypeDef* hqspi;

private:
    HAL_StatusTypeDef QSPI_HAL_Command(QSPI_CommandTypeDef *cmd) const;
    HAL_StatusTypeDef QSPI_HAL_Transmit(uint8_t *pData) const;
};

#endif