//
// Created by 14135 on 24-12-13.
//

#include <cstdio>
#include "qspi.h"

QSPI::QSPI(QSPI_HandleTypeDef *hqspi) {
    this->hqspi = hqspi;
}

HAL_StatusTypeDef QSPI::QSPI_HAL_Command(QSPI_CommandTypeDef *cmd) const{
    return HAL_QSPI_Command(this->hqspi, cmd, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//    return HAL_QSPI_Command_IT(this->hqspi, cmd);
}

HAL_StatusTypeDef QSPI::QSPI_HAL_Transmit(uint8_t *pData) const{
    return HAL_QSPI_Transmit(this->hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//    return HAL_QSPI_Transmit_IT(this->hqspi, pData);
}

int QSPI::sendCommand() {
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = 0;

    return QSPI_HAL_Command(&sCommand);
}

int QSPI::sendCommand(uint8_t cmd) {
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0x000000 | (cmd << 8);
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = 0;

    return QSPI_HAL_Command(&sCommand);
}

int QSPI::sendData(uint8_t data) {
    uint8_t _data[] = {data};
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x32;
    sCommand.Address = 0x003C00;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 0;
    sCommand.NbData = 1;
    QSPI_HAL_Command(&sCommand);
    return QSPI_HAL_Transmit(_data);
}

int QSPI::sendData(uint8_t *data, uint8_t len) {
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x32;
    sCommand.Address = 0x003C00;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 0;
    sCommand.NbData = len;
    QSPI_HAL_Command(&sCommand);
    return QSPI_HAL_Transmit(data);
}

int QSPI::sendCommand(uint8_t cmd, uint8_t data) {
    uint8_t _data[1] = {data};

    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0x000000 | (cmd << 8);
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = 1;

    HAL_StatusTypeDef commandStatus = QSPI_HAL_Command(&sCommand);
    HAL_StatusTypeDef dataStatus = QSPI_HAL_Transmit(_data);

    return commandStatus | (dataStatus << 4);
}


int QSPI::sendCommand(uint8_t cmd, uint16_t data, uint16_t data2) {
    uint8_t _data[4] = {(uint8_t) ((data >> 8) & 0xFF), (uint8_t) (data & 0xFF), (uint8_t) ((data2 >> 8) & 0xFF),
                        (uint8_t) (data2 & 0xFF)};
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0x000000 | (cmd << 8);
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = 4;

    HAL_StatusTypeDef commandStatus = QSPI_HAL_Command(&sCommand);
    HAL_StatusTypeDef dataStatus = QSPI_HAL_Transmit(_data);

    return commandStatus | (dataStatus << 4);
}

int QSPI::sendCommand(uint8_t cmd, uint8_t *data, uint8_t len) {
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x02;
    sCommand.Address = 0x000000 | (cmd << 8);
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.NbData = len;

    HAL_StatusTypeDef commandStatus = QSPI_HAL_Command(&sCommand);
    HAL_StatusTypeDef dataStatus = QSPI_HAL_Transmit(data);

    return commandStatus | (dataStatus << 4);
}

int QSPI::sendCommandWithInstruction(uint8_t instruction, uint8_t cmd, uint8_t *data, uint8_t len) {
    QSPI_CommandTypeDef sCommand{};
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = instruction;
    sCommand.Address = 0x000000 | (cmd << 8);
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 0;
    sCommand.NbData = len;

    HAL_StatusTypeDef commandStatus = QSPI_HAL_Command(&sCommand);
    HAL_StatusTypeDef dataStatus = QSPI_HAL_Transmit(data);

    return commandStatus | (dataStatus << 4);
}

int QSPI::sendCommandList(init_line_t *init_operations, uint8_t len) {
    for (int i = 0; i < len; i++) {
        if (init_operations[i].cmd == 0) {
            HAL_Delay(init_operations[i].data[0]);
            continue;
        }
        if (init_operations[i].len == 0) {
            return sendCommand(init_operations[i].cmd, 0x00) << 8 | i;
        } else {
            return sendCommand(init_operations[i].cmd, init_operations[i].data, init_operations[i].len) << 8 | i;
        }
    }
    return 0;
}

int QSPI::sendCommandList2(const uint8_t *operations, size_t len) {
    for (size_t i = 0; i < len; ++i)
    {
        uint8_t l = 0;
        switch (operations[i])
        {
            case BEGIN_WRITE:
//                beginWrite();
                break;
            case WRITE_C8_D16:

                break;
            case WRITE_C8_D8:
//                writeC8D8(operations[++i], operations[++i]);
                sendCommand(operations[++i]);
                sendData(operations[++i]);
                break;
            case WRITE_COMMAND_8:
//                writeCommand(operations[++i]);
                sendCommand(operations[++i]);
                break;
            case WRITE_C16_D16:

                break;
            case WRITE_COMMAND_16:

                break;
            case WRITE_DATA_8:
                l = 1;
                break;
            case WRITE_DATA_16:
                l = 2;
                break;
            case WRITE_BYTES:
                l = operations[++i];
                break;
            case END_WRITE:
//                endWrite();
                break;
            case DELAY:
                HAL_Delay(operations[++i]);
                break;
            default:
                printf("Unknown operation id at %d: %d", i, operations[i]);
                break;
        }
        while (l--)
        {
            sendData(operations[++i]);
        }
    }
    return 0;
}







