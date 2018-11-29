#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <getopt.h>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map <string, int> aaa;
    aaa["abc"] = 12;
    aaa["cde"] = 12121;
    aaa[ "dsfiusdhfoisadh"] = 129982179;
    for (auto it = aaa.begin(); it != aaa.end(); it++)
    {
        cout << it->second << endl;
    }


    return 0;
}