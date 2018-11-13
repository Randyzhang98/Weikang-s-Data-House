#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <math.h>

using namespace std;

int main(int argc, char*argv[])
{
    srand(unsigned(time(48)));
    ofstream oFile;
    int len = pow(10,atoi(argv[3]))/2;
    int tp = atoi(argv[4]);
    if (argc == 5 && tp == 0)
    {
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        for (int i = 0; i < len; i++)
        {
            oFile << i << endl;
        }
    }
    else if (argc == 5 && tp == 1)
    {
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        for (int i = len - 1 ; i >= 0; i--)
        {
            oFile << i << endl;
        }
    }
    else if (argc == 5 && tp == 2)
    {
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        for (int i = len - 1 ; i >= 0; i--)
        {
            oFile << 0 << endl;
        }
    }
    else 
    {
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        oFile << len/2 << endl;
        for (int i = 0; i < len; i++)
        {
            oFile << mrand48() << endl;
        }
    }
    return 0;    
}