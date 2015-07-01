/* 
 * File:   Wheel.h
 * Author: Justin
 *
 * Created on 2015年7月1日, 下午 9:28
 */

#ifndef WHEEL_H
#define	WHEEL_H

#include <Utility/MT/ManualResetEvent.h>

using namespace KGI_TW_Der_Utility;

class Wheel {
public:
    Wheel( int forward, int backward, int pwm );
    Wheel(const Wheel& orig);
    virtual ~Wheel();
    
    Wheel& operator=( const Wheel& orig );
    
    void Stop();
    void Forward( int speed );
    void Backward( int speed );
    void Break();
    
private:
    void PWMOutput();
private:
    int m_PinForward, m_PinBackward, m_PinPWM;
    bool m_IsStopPWM;
    int m_CrtSpeed;
    ManualResetEvent m_EventPWM;

};

#endif	/* WHEEL_H */

