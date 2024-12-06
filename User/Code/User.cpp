//
// Created by 14135 on 24-12-6.
//

#include <cstdio>
#include "User.h"
#include "CO5300_driver.h"
#include "cmsis_os2.h"
CO5300 co5300;

void setup() {
    co5300.init();
}

void loop() {
    osDelay(2000);
    printf("Hello World!\n");
    co5300.init();
}