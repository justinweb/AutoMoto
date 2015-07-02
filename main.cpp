/* 
 * File:   main.cpp
 * Author: Justin
 *
 * Created on 2015年6月28日, 下午 9:38
 */

#include <cstdlib>
#include <Utility/Log/LogSystem.h>
#include <Utility/DateTime.h>
#include <Utility/StringTemplateUtil.h>
#include <wiringPi.h>
#include "MotoL298N.h"
#include "Wheel.h"
#include "DHT11Reader.h"

using namespace std;
using namespace KGI_TW_Der_Utility;

int TestWheel();
int TestDHT11();
/*
 * 
 */
int main(int argc, char** argv) {
    //return TestWheel();
    return TestDHT11();
    
    DateTime now;
    std::string msg;
    StringTemplateUtil::Format( msg, "Date=%04d%02d%02d %02d:%02d:%02d", now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond() );
    printf( "%s\r\n", msg.c_str() );
    MotoL298N a;
    return 0;
}

int TestWheel(){
    //wiringPiSetupSys();
    wiringPiSetup();
    Wheel wheel( 27,28,29 );
    bool isStop = false;
    char speed;
    while(!isStop){
        printf("[f|b|s|q]?\r\n");
        char c = getchar();
        if( c == '\n' )
            continue;
        switch( c ){
            case 'f':
            case 'b':{
                printf( "Speed [0-9]?\r\n" );
                do{
                    speed = getchar();
                }
                while(speed == '\n' );
                if( speed >= '0' && speed < '9' ){
                    switch( c ){
                        case 'f':
                            wheel.Forward( speed - 0x30 );
                            break;
                        case 'b':
                            wheel.Backward( speed - 0x30 );
                            break;
                    }
                }else{
                    printf( "Speed must be 0 ~ 9\r\n" );
                }
            }
            break;
            case 's':
                wheel.Stop();
                break;
            case 'q':     
                isStop = true;
                break;
        }
    }
}

int TestDHT11(){
    wiringPiSetup();
    
//    pinMode(27,OUTPUT);
//    digitalWrite( 27, HIGH );
//    delay(1000);
//    digitalWrite( 27, LOW );
    
    DHT11Reader dht11(27);
    for( int i = 1; i < 6; ++i ){
        dht11.Read();
        delay(3000);
    }
    return 0;
}