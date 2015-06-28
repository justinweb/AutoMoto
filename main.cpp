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
#include "MotoL298N.h"

using namespace std;
using namespace KGI_TW_Der_Utility;

/*
 * 
 */
int main(int argc, char** argv) {
    DateTime now;
    std::string msg;
    StringTemplateUtil::Format( msg, "Date=%04d%02d%02d %02d:%02d:%02d", now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond() );
    printf( "%s\r\n", msg.c_str() );
    MotoL298N a;
    return 0;
}

