#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <getopt.h>

#include "playground.h"

using namespace std;

vector<string> ttt_list;

int main (int argc, char * argv[])
{

    playground_t & playground = playground_t::getInstance();

    bool verbose_flag = false;
    bool median_flag = false;
    bool midpoint_flag = false;
    bool transfers_flag = false;
    bool ttt_flag = false;

    //unsigned current_time_stamp = 0;

    const option long_options[] = {
        {"verbose",   no_argument,       0, 'v'},
        {"median",    no_argument,       0, 'm'},
        {"midpoint",  no_argument,       0, 'p'},
        {"transfers", no_argument,       0, 't'},
        {"ttt",       required_argument, 0, 'g'},
        {0,0,0,0}
    };

    int c = -1;
    while ( (c = getopt_long(argc, argv, "vmptg:", long_options, NULL)) != -1 )
    {
        switch (c)
        {
            case 'v':
                verbose_flag = true;
                break;
            case 'm':
                median_flag = true;
                break;
            case 'p':
                midpoint_flag = true;
                break;
            case 't':
                transfers_flag = true;
                break;
            case 'g':
                ttt_flag = true;
                playground.ttt_holder_adder(optarg);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
    //ttt_part
    playground.setFlag(verbose_flag, median_flag, midpoint_flag, transfers_flag, ttt_flag);
    playground.stagement();
    playground.conclusion();

    return 0;
}