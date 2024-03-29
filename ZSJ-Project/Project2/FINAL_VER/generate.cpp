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
    srand(unsigned(time(NULL)));
    ofstream oFile;
    int len = 2000000*atoi(argv[3]);
    int tp = atoi(argv[4]);
    if (argc == 5 && tp == 0)
    {
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        oFile << 0 << endl;
        for (int i = 0; i < len; i++)
        {
            oFile << mrand48() << endl;
        }
    }
    else if (argc == 5 && tp == 1)
    {
       
        string file_name(argv[1]);
        oFile.open(file_name);
        oFile << argv[2] << endl;
        oFile << len << endl;
        oFile << len -1  << endl;
        for (int i = 0; i < len; i++)
        {
            oFile << mrand48() << endl;
        }
    }
    else if (argc == 5 && tp == 2)
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