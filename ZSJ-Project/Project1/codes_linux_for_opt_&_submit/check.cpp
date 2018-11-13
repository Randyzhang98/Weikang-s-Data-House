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
   int a, b;
    //cout << tt;
    //cout << a;
    iFile >> a;
    while (iFile >> b)
    {
        //cout << b << endl;
        if (b < a) cout << "error";
        a = b;
    }
    return 0;
}