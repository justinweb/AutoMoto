/* 
 * File:   Wheel.cpp
 * Author: Justin
 * 
 * Created on 2015年7月1日, 下午 9:28
 */

#include "Wheel.h"
#include <wiringPi.h>
#include <thread>

Wheel::Wheel(int forward, int backward, int pwm) : m_PinForward(forward), m_PinBackward(backward), m_PinPWM(pwm) {
    pinMode( m_PinForward, OUTPUT );
    pinMode( m_PinBackward, OUTPUT );
    pinMode( m_PinPWM, OUTPUT );
    m_CrtSpeed = 0;
    m_IsStopPWM = false;
    std::thread tPWM( std::bind(&Wheel::PWMOutput, this) );
    tPWM.detach();
}

Wheel::Wheel(const Wheel& orig) {
    *this = orig;
}

Wheel::~Wheel() {
    m_IsStopPWM = true;
    m_EventPWM.Set(true);
}

Wheel& Wheel::operator=( const Wheel& orig ){
    if( this != &orig ){
        m_PinForward = orig.m_PinForward;
        m_PinBackward = orig.m_PinBackward;
        m_PinPWM = orig.m_PinPWM;
    }
    return *this;
}

void Wheel::Stop(){
    m_CrtSpeed = 0;
    digitalWrite( m_PinForward, LOW );
    digitalWrite( m_PinBackward, LOW );
    digitalWrite( m_PinPWM, LOW );    
}
    
void Wheel::Forward( int speed ){
    if( speed <= 0 )
        Stop();
    else{
        digitalWrite( m_PinForward, HIGH );
        digitalWrite( m_PinBackward, LOW );
        if( speed > 10 )
            m_CrtSpeed = 10;
        else
            m_CrtSpeed = speed;
        
        m_EventPWM.Set(true);
    }
}
    
void Wheel::Backward( int speed ){
    if( speed <= 0 )
        Stop();
    else{
        digitalWrite( m_PinForward, LOW );
        digitalWrite( m_PinBackward, HIGH );
        if( speed > 10 )
            m_CrtSpeed = 10;
        else
            m_CrtSpeed = speed;
        
        m_EventPWM.Set(true);
    }
}
    
void Wheel::Break(){
    digitalWrite( m_PinForward, HIGH );
    digitalWrite( m_PinBackward, HIGH );
    digitalWrite( m_PinPWM, HIGH );
    m_CrtSpeed = 0;
}

void Wheel::PWMOutput(){
    m_EventPWM.Reset();
    while(!m_IsStopPWM){
        if( m_CrtSpeed <= 0 ){
            m_EventPWM.Wait(0);
        }else{
            int delayMs = 1000 / (m_CrtSpeed*2);
            digitalWrite( m_PinPWM, HIGH );
            delay(delayMs);
            digitalWrite( m_PinPWM, LOW );
            delay(delayMs);
            //printf( "PWMOutput ...\r\n" );
        }
        
        m_EventPWM.Reset();
    }
    
}

