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
        int pathcost = 0, weight;
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

int column, row;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int step = 0;

point_t start, ed;

void retriver (point_t**  map, const point_t tracker)
{
    if (tracker.x != start.x || tracker.y != start.y)
    {
        retriver(map, map[tracker.pre_x][tracker.pre_y]);
    }
    cout << "(" << tracker.x << ", " << tracker.y << ")" << endl;
}

void verbose_word_1(const point_t &C) {
    std::cout << "Step " << step++ << "\n";
    std::cout << "Choose cell (" << C.x << ", " << C.y << ") with accumulated length " <<  C.pathcost << ".\n";
}

void verbose_word_2(const point_t &C) {
    std::cout << "Cell (" << C.x << ", " << C.y << ") with accumulated length " <<  C.pathcost << " is added into the queue." << "\n";
}

void verbose_word_3(const point_t &C) {
    std::cout << "Cell (" << C.x << ", " << C.y << ") with accumulated length " <<  C.pathcost << " is the ending point." << "\n";
}


// bool has_neighbour_in_this_dir (point_t C, unsigned i)
// {
//     int neighbour_x = C.x + dx[i];
//     int neighbour_y = C.y + dy[i];
//     return (neighbour_x >=0 && neighbour_y >= 0 && neighbour_x < column && neighbour_y < row);
// }

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
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
    int column, row;
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
        int neighbour_x, neighbour_y;
        bool end_flag = false;
        point_t C = queue->dequeue_min();
        if (verbose_mode)
        {
            verbose_word_1(C);
        }
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
                    if (neighbour_x == ed.x && neighbour_y == ed.y)
                    {
                        end_flag = true;
                        if (verbose_mode)
                        {
                            verbose_word_3(V);
                        }
                        break;
                    }
                    if (verbose_mode)
                    {
                        verbose_word_2(V);
                    }
                    queue->enqueue(V);
                }
            }
        }
        if (end_flag) break;
    }

    //trace back
    cout << "The shortest path from (" << start.x << ", " << start.y << ") to (" << ed.x << ", " << ed.y << ") is " << map[ed.x][ed.y].pathcost << "." << endl;;
    cout << "Path:" << endl;
    point_t temp = map[ed.x][ed.y];
    retriver(map, temp);
    


    




    // // this is the initializing of the points map;
    // points = new point_t* [column];
    // for (i = 0; i < column; i++)
    // {
    //     points[i] = new point_t [row];
    // }
    // for (i = 0; i < column; i++)
    // {
    //     for (j = 0; j < row; j++)
    //     {
    //         points[i][j]->x = i;
    //         points[i][j]->y = j;

    //     }
    // }


    for (i = 0; i < column; i++)
    {
        delete [] map[i];
    }
    delete [] map;

    delete queue;
    return 0;
}