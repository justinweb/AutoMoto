/* 
 * File:   SoftwarePWM.cpp
 * Author: Justin
 * 
 * Created on 2015年7月21日, 下午 10:12
 */

#include "SoftwarePWM.h"
#include <wiringPi.h>
#include <thread>

SoftwarePWM::SoftwarePWM(AutoMoto::WiPiPinNumber wiPiPinNumber) : m_WiPiPinNumber(wiPiPinNumber), m_Level(0), m_OrgLevel(0),m_IsRunning(false) {
}

//SoftwarePWM::SoftwarePWM(const SoftwarePWM& orig) {
//}

SoftwarePWM::~SoftwarePWM() {
}

void SoftwarePWM::Start(){
    m_IsRunning = true;
    std::thread tPWM( std::bind(&SoftwarePWM::PWMThread,this) );
    tPWM.detach();
}

void SoftwarePWM::Stop(){
    m_IsRunning = false;
}

void SoftwarePWM::PWMThread(){
    int onTime,offTime;
    while(m_IsRunning){
        if( m_Level != m_OrgLevel ){
            onTime = m_Level * 1200;
            offTime = (10 - m_Level) * 1200;
            m_OrgLevel = m_Level;
        }
        
        digitalWrite( 29, HIGH );
        delayMicroseconds(onTime);
        digitalWrite( 29, LOW );
        delayMicroseconds(offTime);
    }
}
