/*
 * Tutorial: https://gflags.github.io/gflags/#validate
 * gflags_demo.cpp
 * /tmp/test -nobig_menu --languages="Chinese,English,Japanese"
 */

#include <iostream>
#include <cstdio>
#include <gflags/gflags.h>

using namespace std;

// 用于声明定义分离
/*
 * DECLARE_bool(big_menu);
 * DECLARE_string(languages);
 */

DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german",
             "comma-separated list of languages to offer in the 'lang' menu");
DEFINE_int32(port, 8888, "What port to listen on");

// 验证函数，看来至少要每种类型一个验证
static 
bool ValidatePort(const char* flagname, gflags::int32 value) 
{
    // cout << "ArgValidator() flagname = " << flagname << " value = " << value << endl;
    if (value > 1024 && value < 32768)   // value is ok
        return true;
    printf("Invalid value for --%s: %d\n", flagname, (int)value);
    return false;
}
// 定义port_dummy为了保证RegisterFlagValidator先于main函数执行
static const bool port_dummy = gflags::RegisterFlagValidator(&FLAGS_port, &ValidatePort);


int main( int argc, char **argv )
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    cout << FLAGS_big_menu << endl;
    cout << FLAGS_languages << endl;
    cout << FLAGS_port << endl;

    return 0;
}
