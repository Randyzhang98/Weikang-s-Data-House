#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <queue>
#include <list>


#define INF (1 << 30)

using namespace std;

class graph_t
{
    public:
        // struct node_t{
        //     typedef std::shared_ptr<node_t> ptr;
        //     unsigned node_this;
        //     int weight;
        //     node_t(unsigned s, int e, int w): node_this(e), weight(w) {}
        // };
        struct node_t 
        {
            typedef std::shared_ptr<node_t> ptr;
            unsigned index;
            int weight;
            node_t(const unsigned & index, const int & weight): index(index), weight(weight) {}
        };
        struct greater_t
        {
            bool operator()(const node_t::ptr x, const node_t::ptr y) const 
            {
                return x->weight > y->weight;
            }
        };
        unsigned num_nodes, num_edges; bool is_DAG = true;
        vector <unsigned> degree;
        
        vector <list <node_t> > adj_list; 
        vector <list <node_t> > adj_list_two_dir;
        // this is adjactent_list part!!!!
        int MST_weight = 0;

        // unordered_map <, vector<unsigned> > pairs; // avoid a->b and b->a;
        // bool no_self_circle = true;

        void edge_adder(unsigned & a, unsigned & b, int & w)
        {
            degree[b]++;
            num_edges++;
            node_t in(b,w);
            adj_list[a].push_back(in);
            adj_list_two_dir[a].push_back(in);
            node_t in_2(a,w);
            adj_list_two_dir[b].push_back(in_2);
        }

        graph_t (unsigned num)
        {
            for (unsigned i = 0; i < num; i++)
            {
                list <node_t> node;
                this->adj_list.push_back(node);
                this->adj_list_two_dir.push_back(node);
                this->degree.push_back(0);
            }
            this->num_nodes = num;
        }

        void topo_traverse()
        {
            queue<unsigned> queue;
            unsigned num_out_order = 0;
            for (unsigned i = 0; i < num_nodes; i++)
            {
                if (degree[i] == 0)
                {
                    // cout << "i is " << i << endl; 
                    queue.push(i);
                }
            }
            // cout << queue.front() << endl;
            // cout << "topo, start!^~^" << endl;
            while (queue.empty() == false)
            {
                num_out_order += 1;
                unsigned v = queue.front();
                queue.pop();
                for (auto j = adj_list[v].begin(); j != adj_list[v].end(); j++)
                {
                    degree [ j->index ] --;
                    if (degree [ j->index ] == 0) queue.push( j->index );
                }
            }
            // cout << " Num_of_out_order is " << num_out_order << endl;
            if (num_out_order == num_nodes) 
            {
                // is_DAG = no_self_circle;
                is_DAG = true;
            }
            else is_DAG = false;
        }

        void DAG_print()
        {
            if (is_DAG) 
            {
                cout << "The graph is" <<  " a DAG" << endl;
            }
            else 
            {
                cout << "The graph is not" <<  " a DAG" << endl;
            }
        }

        bool x_or (const bool & a, const bool & b)
        {
            if ( (a && b) || (!a && !b) )
            {
                return false;
            }
            else return true;
        }

        void find_MST()
        {
            std::vector<bool> node_is_visited(num_nodes, false);
            unsigned num_visited_nodes = 0;
            vector <unsigned> visted_nodes_index;
            visted_nodes_index.push_back(0); 
            vector <int> MST_map(num_nodes, INF);
            MST_map[0] = 0;
            priority_queue <node_t::ptr, vector<node_t::ptr>, greater_t > D;
            D.emplace(make_shared<node_t> (0,0) );
            while (!D.empty())
            {
                unsigned a = D.top()->index;
                int b = D.top()->weight;
                D.pop();
                if (node_is_visited[a]) continue;
                MST_weight += b;
                node_is_visited[a] = true;
                for (auto j = adj_list_two_dir[a].begin(); j != adj_list_two_dir[a].end(); j++ )
                {
                    
                    if (!node_is_visited[j->index] && j->weight < MST_map[j->index])
                    {
                        MST_map[j->index] = j->weight;
                        D.emplace(make_shared<node_t> (j->index, j->weight) );
                    }
                }
                num_visited_nodes++;
            }

            if (num_visited_nodes == num_nodes) 
            {
                cout << "The total weight of MST is " << MST_weight << endl;
            }
            else 
            {
                cout << "No MST exists!\n"; 
            }
        }   
};



int main(int argc, char const *argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    // double d = clock();

    unsigned num;
    stringstream line_buffer;
    string line;
    getline(cin, line);
    line_buffer << line;
    line_buffer >> num;
    line_buffer.clear();

    graph_t graph(num);

    

    unsigned a, b;
    int w;
    bool flag = false;

    while (getline(cin, line) && !line.empty())
    {
        flag = true;
        line_buffer << line;
        line_buffer >> a >> b >> w;
        line_buffer.clear();
        // cout << a << " " << b << " " << w << endl;
        graph.edge_adder(a,b,w);
    }
    if (flag)
    {
        graph.topo_traverse();
        graph.DAG_print();
        // graph.plotE();
        graph.find_MST();

    }
    else 
    {
        cout << "The graph is" <<  " a DAG" << endl;
        cout << "No MST exists!" << endl;
    }
    
    // cout << double( (clock() - d)/CLOCKS_PER_SEC ) << endl;


    return 0;
}

