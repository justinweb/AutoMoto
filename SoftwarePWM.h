/* 
 * File:   SoftwarePWM.h
 * Author: Justin
 *
 * Created on 2015年7月21日, 下午 10:12
 */

#ifndef SOFTWAREPWM_H
#define	SOFTWAREPWM_H

#include "AutoMotoCommon.h"

class SoftwarePWM {
public:
    SoftwarePWM(AutoMoto::WiPiPinNumber wiPiPinNumber);
    SoftwarePWM(const SoftwarePWM& orig) = delete;
    virtual ~SoftwarePWM();
    
    void Start();
    void Stop();
    
    int GetLevel() const { return m_Level; }
    void SetLevel( int level ){ m_Level = level; }
private:
    AutoMoto::WiPiPinNumber m_WiPiPinNumber;
    int m_Level,m_OrgLevel;
    bool m_IsRunning;
private:
    void PWMThread();

};

#endif	/* SOFTWAREPWM_H */

