//
// Created by 14135 on 24-12-6.
//

#include <cstdio>
#include "User.h"
#include "CO5300_driver.h"
//#include "cmsis_os2.h"

QSPI qspi = QSPI(&hqspi);
CO5300 co5300 = CO5300(&qspi, GPIOB, GPIO_PIN_0);

void setup() {
    co5300.init();
    HAL_Delay(1);
    co5300.display_on();
}

void loop() {
    for(uint8_t i = 100; i < 255; i++){
        HAL_Delay(200);
        int state = co5300.set_brightness(i);
        if(state != HAL_OK){
            printf("set brightness failed, state: %d\n", state);
        }
    }
}