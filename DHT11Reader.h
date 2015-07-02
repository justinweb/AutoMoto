/* 
 * File:   DHT11Reader.h
 * Author: Justin
 *
 * Created on 2015年7月2日, 下午 11:27
 */

#ifndef DHT11READER_H
#define	DHT11READER_H

#include <wiringPi.h>

class DHT11Reader {
public:
    DHT11Reader( int dataPin );
    DHT11Reader(const DHT11Reader& orig);
    virtual ~DHT11Reader();
    
    bool Read();
private:
    int m_DataPin;              // for wiringPi
    int m_DHT11Data[5];

};

#endif	/* DHT11READER_H */

