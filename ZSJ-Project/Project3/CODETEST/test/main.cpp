#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "binary_heap.h"
#include "unsorted_heap.h"
#include "fib_heap.h"

using namespace std;

class point_t
{
    public:
        unsigned x, y;
        unsigned pathcost = 0, weight;
        bool reached = false;
        unsigned pre_x, pre_y;
};

struct compare_t
{
    bool operator() (const point_t &a, const point_t &b) const
    {
        if (a.pathcost == b.pathcost)
        {
            if (a.x != b.x) return a.x < b.x;
            else return a.y < b.y;
        }
        return a.pathcost < b.pathcost;
    }
};

unsigned column, row;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
unsigned step = 0;

point_t start, ed;


int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    double b = clock();
    unsigned i,j;
    //getopt
    bool verbose_mode = false;
    string impl;
    const option long_options[] = { 
        {"implementation", required_argument, NULL, 'i'},
        {"verbose", no_argument, NULL, 'v'},
        {0,0,0,0}
    };
    int c = -1;
    while ( (c = getopt_long(argc, argv, "vi:", long_options, NULL)) != -1 )
    {
        switch (c)
        {
            case 'v':
                verbose_mode = true;
                break;
            case 'i':
                impl = optarg;
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }

    priority_queue<point_t , compare_t> *queue;
    if (impl == "BINARY") queue = new binary_heap<point_t , compare_t>();
    else if (impl == "UNSORTED") queue = new unsorted_heap<point_t , compare_t>();
    else if (impl == "FIBONACCI") queue = new fib_heap<point_t , compare_t>();
    else {cout << "Invalid input" << endl; return 0;}    

    //this is the initializing of the points map;
    cin >> column >> row;
    cin >> start.x >> start.y >> ed.x >> ed.y;
    point_t** map = new point_t* [column];
    for (i = 0; i < column; i++)
    {
        map[i] = new point_t [row];
    }
    for (j = 0; j < row; j++)
    {
        for (i = 0; i < column; i++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
            cin >> map[i][j].weight;
            map[i][j].pre_x = i;
            map[i][j].pre_y = j;
        }
    }

    //pathchecker part
    map[start.x][start.y].reached = true;
    map[start.x][start.y].pathcost = map[start.x][start.y].weight;

    queue->enqueue(map[start.x][start.y]);


    while (!queue->empty())
    {
        unsigned neighbour_x, neighbour_y;
        bool end_flag = false;
        point_t C = queue->dequeue_min();
        for (i = 0; i < 4; i++)
        {
            if (end_flag) break;
            neighbour_x = C.x + dx[i];
            neighbour_y = C.y + dy[i];
            if (neighbour_x >=0 && neighbour_y >= 0 && neighbour_x < column && neighbour_y < row )
            {
                //cout << "here neighbour is " <<"(" << neighbour_x << ", " << neighbour_y << ")"  << endl;
                point_t &V = map[neighbour_x][neighbour_y];
                if (!V.reached)
                {
                    V.reached = true;
                    V.pathcost = C.pathcost + V.weight;
                    V.pre_x = C.x;
                    V.pre_y = C.y;
                    queue->enqueue(V);
                }
            }
        }
        if (end_flag) break;
    }

    for (i = 0; i < column; i++)
    {
        delete [] map[i];
    }
    delete [] map;

    delete queue;

    double r = (clock() - b) * 1.0 / CLOCKS_PER_SEC;

    cout << r << endl; 

    return 0;
}