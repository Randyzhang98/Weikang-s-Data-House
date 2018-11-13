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
    string file_name(argv[1]);
    oFile.open(file_name);
    oFile << argv[2] << endl;
    int len = pow(10,atoi(argv[3]))/2;
    oFile << len << endl;
    for (int i = 0; i < len; i++)
    {
        oFile << mrand48() << endl;
    }
    return 0;    
}