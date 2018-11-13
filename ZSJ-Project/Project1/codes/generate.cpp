#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    ofstream oFile;
    oFile.open("test");
    oFile << 5 << endl;
    oFile << 20 << endl;
    for (int i = 0; i < 20; i++)
    {
        oFile << mrand48() << endl;
    }
    return 0;    
}