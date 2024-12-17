////
//// Created by 14135 on 24-12-5.
////
//
#include <cstdio>
#include "CO5300_driver.h"
#include "quadspi.h"
//
//CO5300::CO5300(QSPI *qspi, GPIO_TypeDef *rst_port, uint16_t rst_pin) {
//    this->qspi = qspi;
//    this->rst_port = rst_port;
//    this->rst_pin = rst_pin;
//    this->_width = CO5300_MAXWIDTH;
//    this->_height = CO5300_MAXHEIGHT;
//}

CO5300::CO5300(QSPI *qspi, GPIO_TypeDef *rst_port, uint16_t rst_pin, uint16_t width,
               uint16_t height) :
        qspi(qspi), rst_port(rst_port), rst_pin(rst_pin), _width(width), _height(height) {

}

int CO5300::CO5300::init() {
    // Initialize the QSPI
    init_line_t init_operations[] = {
            {CO5300_C_SLPOUT,             0, {0}},
            {0x00,                        1, {CO5300_SLPOUT_DELAY}},
            {0xFE,                        1, {0}},
            {CO5300_W_SPIMODECTL,         1, {0x80}},
            {CO5300_W_PIXFMT,             1, {0x77}},//0x77:888, 0x66:666, 0x55:565
            {CO5300_W_WCTRLD1,            1, {0x20}},
//            {0x00,                        1, {1}},
            {CO5300_W_WDBRIGHTNESSVALHBM, 1, {0xFF}},
            {CO5300_W_CASET, 4, {0x00, 0x14, 0x01, 0x2B}},
            {CO5300_W_PASET, 4, {0x00, 0x00, 0x01, 0xC7}},
            {CO5300_C_DISPON,             0, {0}},
            {CO5300_W_WDBRIGHTNESSVALNOR, 1, {0x00}},
//            {0x00,                        1, {1}},
            {CO5300_W_WCE,                1, {0x00}},
            {0,                           1, {10}}
    };

    //rst the co5300 ic
    HAL_GPIO_WritePin(this->rst_port, this->rst_pin, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(this->rst_port, this->rst_pin, GPIO_PIN_RESET);
    HAL_Delay(CO5300_RST_DELAY);
    HAL_GPIO_WritePin(this->rst_port, this->rst_pin, GPIO_PIN_SET);
    HAL_Delay(CO5300_RST_DELAY);

//    int init_state = this->qspi->sendCommandList(init_operations, sizeof(init_operations) / sizeof(init_line_t));
    int init_state = this->qspi->sendCommandList2((uint8_t *) co5300_init_operations, sizeof(co5300_init_operations));
    if (init_state != HAL_OK) {
        int error_position = init_state & 0xFF;
        int error_code1 = (init_state >> 8) & 0xFF;
        int error_code2 = (init_state >> 16) & 0xFF;
        printf("CO5300 init failed, error position: %d, error code1: %d, error code2: %d\n", error_position,
               error_code1, error_code2);
    }
//    HAL_Delay(1);

    init_state = this->qspi->sendCommand(CO5300_C_INVOFF);
    if (init_state != HAL_OK) {
        printf("CO5300 init invert failed, error code:%d\n", init_state);
    }
//    HAL_Delay(1);

    init_state = this->qspi->sendCommand(CO5300_W_MADCTL, CO5300_MADCTL_COLOR_ORDER | CO5300_MADCTL_X_AXIS_FLIP |
                                                          CO5300_MADCTL_Y_AXIS_FLIP);
    if (init_state != HAL_OK) {
        printf("CO5300 init rotation failed, error code:%d\n", init_state);
    }
//    HAL_Delay(1);

    init_state = this->qspi->sendCommand(CO5300_W_CASET, (uint16_t) 0, this->_width - 1);
//    init_state = this->qspi->sendCommand(CO5300_W_CASET);
//    uint8_t w[] = {(uint8_t)(this->_width >> 8), (uint8_t)(this->_width & 0xff)};
//    uint8_t h[] = {(uint8_t)(this->_height >> 8), (uint8_t)(this->_height & 0xff)};
//    init_state = this->qspi->sendData(w, 2);
//    init_state = this->qspi->sendData(h, 2);
    if (init_state != HAL_OK) {
        printf("CO5300 init w CASET failed, error code:%d\n", init_state);
    }
    HAL_Delay(1);

    init_state = this->qspi->sendCommand(CO5300_W_PASET, (uint16_t) 0, this->_height - 1);
    if (init_state != HAL_OK) {
        printf("CO5300 init w PASET failed, error code:%d\n", init_state);
    }
    HAL_Delay(1);

    init_state = this->qspi->sendCommand(CO5300_W_RAMWR);
    if (init_state != HAL_OK) {
        printf("CO5300 init w RAMWR failed, error code:%d\n", init_state);
    }

    return init_state;
}

int CO5300::set_brightness(uint8_t brightness) {
    return this->qspi->sendCommand(CO5300_W_WDBRIGHTNESSVALNOR, brightness);
}

int CO5300::display_on() {
    int state = this->qspi->sendCommand(CO5300_C_DISPON);
    if (state != HAL_OK) {
        printf("CO5300 display on failed, error code:%d\n", state);
    }
    HAL_Delay(CO5300_SLPIN_DELAY);
    state = this->qspi->sendCommand(CO5300_C_SLPOUT);
    if (state != HAL_OK) {
        printf("CO5300 display sleep out failed, error code:%d\n", state);
    }
    return state;
}

int CO5300::draw_pixel888(uint16_t x, uint16_t y, uint32_t color) {
//    int state = this->qspi->sendCommand(CO5300_W_CASET, x, x);
//    if (state != HAL_OK) {
//        printf("w CASET failed, error code:%d\n", state);
//    }
////    HAL_Delay(1);
//
//    state = this->qspi->sendCommand(CO5300_W_PASET, y, y);
//    if (state != HAL_OK) {
//        printf("w PASET failed, error code:%d\n", state);
//    }
////    HAL_Delay(1);

    int state = this->qspi->sendCommand(CO5300_W_RAMWR);
    if (state != HAL_OK) {
        printf("w RAMWR failed, error code:%d\n", state);
    }
//    HAL_Delay(1);

    uint8_t color_data[3] = {(uint8_t) ((color >> 16) & 0xff), (uint8_t) ((color >> 8) & 0xff), (uint8_t) ((color >> 8) & 0xff)};
    state = this->qspi->sendData(color_data, 3);
//    state = this->qspi->sendCommandWithInstruction(0x32, CO5300_W_RAMWR, color_data, 2);
//    state = this->qspi->sendCommandWithInstruction(0x32, CO5300_W_WRMC, color_data, 2);
    if (state != HAL_OK) {
        printf("w WRMC failed, error code:%d\n", state);
    }
//    HAL_Delay(1);

    return state;
}

