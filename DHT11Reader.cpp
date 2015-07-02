/* 
 * File:   DHT11Reader.cpp
 * Author: Justin
 * 
 * Created on 2015年7月2日, 下午 11:27
 */

#include "DHT11Reader.h"
#include <memory.h>
#include <stdio.h>
#include <stdint.h>
#define MAXTIMINGS	85

DHT11Reader::DHT11Reader(int dataPin) : m_DataPin(dataPin) {
}

DHT11Reader::DHT11Reader(const DHT11Reader& orig) {
}

DHT11Reader::~DHT11Reader() {
}

bool DHT11Reader::Read(){
    memset( m_DHT11Data, 0, sizeof(int)*5 );
    
    uint8_t laststate	= HIGH;
    uint8_t counter		= 0;
    uint8_t j		= 0, i;
    float	f; /* fahrenheit */

    /* pull pin down for 18 milliseconds */
    pinMode( m_DataPin, OUTPUT );
    digitalWrite( m_DataPin, LOW );
    delay( 18 );
    /* then pull it up for 40 microseconds */
    digitalWrite( m_DataPin, HIGH );
    delayMicroseconds( 40 );
    /* prepare to read the pin */
    pinMode( m_DataPin, INPUT );

    /* detect change and read data */
    for ( i = 0; i < MAXTIMINGS; i++ )
    {
            counter = 0;
            while ( digitalRead( m_DataPin ) == laststate )
            {
                    counter++;
                    delayMicroseconds( 1 );
                    if ( counter == 255 )
                    {
                            break;
                    }
            }
            laststate = digitalRead( m_DataPin );

            if ( counter == 255 )
                    break;

            /* ignore first 3 transitions */
            if ( (i >= 4) && (i % 2 == 0) )
            {
                    /* shove each bit into the storage bytes */
                    m_DHT11Data[j / 8] <<= 1;
                    if ( counter > 16 )
                            m_DHT11Data[j / 8] |= 1;
                    j++;
            }
    }

    /*
     * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
     * print it out if data is good
     */
    if ( (j >= 40) &&
         (m_DHT11Data[4] == ( (m_DHT11Data[0] + m_DHT11Data[1] + m_DHT11Data[2] + m_DHT11Data[3]) & 0xFF) ) )
    {
            f = m_DHT11Data[2] * 9. / 5. + 32;
            printf( "Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n",
                    m_DHT11Data[0], m_DHT11Data[1], m_DHT11Data[2], m_DHT11Data[3], f );
    }else  {
            printf( "Data not good, skip\n" );
    }    
}

