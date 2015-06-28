/* 
 * File:   MotoL298N.cpp
 * Author: Justin
 * 
 * Created on 2015年6月27日, 下午 10:24
 */

#include "MotoL298N.h"
#include <wiringPi.h>
#include <stdio.h>

#define _MOTOR_PIN_1_ 27            // for GPIO 16
#define _MOTOR_PIN_2_ 28            // for GPIO 20

MotoL298N::MotoL298N() {
    wiringPiSetup();
    pinMode( _MOTOR_PIN_1_, OUTPUT );
    pinMode( _MOTOR_PIN_2_, OUTPUT );
    
    digitalWrite( _MOTOR_PIN_1_, HIGH );
    delay(500);
    char c = getchar();
    digitalWrite( _MOTOR_PIN_1_, LOW );
}

MotoL298N::MotoL298N(const MotoL298N& orig) {
}

MotoL298N::~MotoL298N() {
}

