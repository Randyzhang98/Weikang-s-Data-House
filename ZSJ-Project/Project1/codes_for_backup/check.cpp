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
    ifstream iFile;
    iFile.open("lsit");
    int i = 0; string tt;
    iFile >> i;
   int a, b;
 //  iFile >> tt;
    //cout << tt;
    //cout << a;
    iFile >> a;
    for (int j = 1; j < i; j++)
    {
        iFile >> b;
        //cout << b << endl;
        if (b < a) cout << "error";
        a = b;
    }
    return 0;
}
