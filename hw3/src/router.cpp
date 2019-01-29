#include "parser.h"
#include <climits>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>

#define INF INT_MAX

class Vertex {
    public:
        Vertex();
        int get_ID();
        int get_predecessor();
        void set_ID(int);
        void set_pred(int);
        double compute_e_cost(int, int);
        void Dijkstra(int, int, int, vector<Vertex*>&, double**, int);
        void trace(int, vector<Vertex*>&, vector<int>&, int, double**, int);
    private:
        int _ID;
        int _predecessor; // up:0  down:1  left:2  right:3  None:-1
};

Vertex::Vertex() {
    _ID = -1;
    _predecessor = -1;
}

int Vertex::get_ID() { return _ID; }
int Vertex::get_predecessor() { return _predecessor; }
void Vertex::set_ID(int id) { _ID = id; }
void Vertex::set_pred(int pred) { _predecessor = pred; }

double compute_e_cost(int usage, int capacity) {
    double cost = pow(2, (double)usage / capacity );
    return cost;
}

void Dijkstra(int source_id, int h, int v, vector<Vertex*>& V, double** e_usage, int capacity) //Algorithm for SSSP 
{
    const int num_vertix = h*v;
    double distance[num_vertix];
    bool visited[num_vertix];
    // initialize
    for (int i = 0 ; i < num_vertix ; ++i) {
        distance[i] = INF;
        visited[i] = false;
    }
    distance[source_id] = 0; 

    class prioritize {
        public:
            bool operator() (pair<int, int>& p1, pair<int, int>& p2) { return p1.second > p2.second; }
    };

    priority_queue< pair<int,int> ,vector<pair<int,int> >, prioritize > pq; //Priority queue to store vertex,weight pairs
    pq.push( make_pair(source_id, distance[source_id]) );
    while ( !pq.empty() ) {
        pair<int, double> curr_pair = pq.top();
        int curr_id = curr_pair.first;
        pq.pop();
        if( visited[curr_id] ) //If the vertex is already visited, no point in exploring adjacent vertices
            continue;
        visited[curr_id] = true; 
        vector<int> adj_id_vec; // store the adj vertex id
        if (curr_id >= 0 && curr_id < h) { // first row of graph
            adj_id_vec.push_back(curr_id + h);
            if (curr_id == h - 1) 
                adj_id_vec.push_back(curr_id - 1);                
            else if (curr_id == 0)
                adj_id_vec.push_back(curr_id + 1);
            else {
                adj_id_vec.push_back(curr_id - 1);
                adj_id_vec.push_back(curr_id + 1);
            }
        }       
        else if (curr_id >= (h - 1) * v) { // last row of graph
            adj_id_vec.push_back(curr_id - h);
            if (curr_id == h * v - 1) 
                adj_id_vec.push_back(curr_id - 1);
            else if (curr_id == (h - 1) * v)
                adj_id_vec.push_back(curr_id + 1);
            else {
                adj_id_vec.push_back(curr_id - 1);
                adj_id_vec.push_back(curr_id + 1);
            }
        }
        else { // middle part of graph
            adj_id_vec.push_back(curr_id - h); // up
            adj_id_vec.push_back(curr_id + h); // down
            if (curr_id % h == 0 || (curr_id + 1) % h == 0) {
                if (curr_id % h == 0)
                    adj_id_vec.push_back(curr_id + 1); // left
                else
                    adj_id_vec.push_back(curr_id - 1); // right
            }
            else {
                adj_id_vec.push_back(curr_id + 1); // left
                adj_id_vec.push_back(curr_id - 1); // right                
            }
        }
        //process adj
        for (int i = 0 ; i < adj_id_vec.size() ; ++i) {
            int adj_id = adj_id_vec[i];
            double cost = compute_e_cost(e_usage[adj_id][curr_id] + 1, capacity);
            if ( !visited[adj_id] && distance[adj_id] > distance[curr_id] + cost) {
                distance[adj_id] = distance[curr_id] + cost;
                V[adj_id] -> set_pred(curr_id);
                pq.push( make_pair(adj_id, distance[curr_id] + cost) );
            }
        }
    }
}

void trace(int id, vector<Vertex*>& V, vector<int>& rt, int i_th, double** e_usage, int h) {
    if ( V[id] -> get_predecessor() !=  -1 ) {
        int pred_id = V[id] -> get_predecessor();
        rt.push_back(id / h);
        rt.push_back(id % h); 
        rt.push_back(pred_id / h);
        rt.push_back(pred_id % h);
        e_usage[id][pred_id] += 1;
        e_usage[pred_id][id] += 1;
        trace( V[id] -> get_predecessor(), V, rt, i_th, e_usage, h);
    }
}

int main(int argc, char **argv)
{
    if( argc < 2 ){ cout << "Usage: ./parser [input_file_name]" << endl; return 1; }

    AlgParser parser;
    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }

    const int x = parser.gNumHTiles();
    const int y = parser.gNumVTiles();
    vector<Vertex*> vertice;
    vertice.reserve(x*y);
    // vertex initialization
    for (int i = 0 ; i < x*y ; ++i) {
        Vertex* v = new Vertex;
        v -> set_ID(i);
        v -> set_pred(-1);
        vertice.push_back(v);
    }
    // edge initialization
    double** edge_usage = new double*[x*y];
    for (int i = 0 ; i < x*y ; ++i) 
        edge_usage[i] = new double[x*y];
    for (int i = 0 ; i < x*y ; ++i) {
        for (int j = 0 ; j < x*y ; ++j)
            edge_usage[i][j] = 0;
    }

    fstream kevin;
    kevin.open(argv[2], ios::out);
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet) {
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );

        int source_id = posS.first + posS.second * parser.gNumHTiles();
        int end_id = posE.first + posE.second * parser.gNumHTiles();
        Dijkstra(source_id, parser.gNumHTiles(), parser.gNumVTiles(), vertice, edge_usage, parser.gCapacity());
        vector<int> i_route;
        trace(end_id, vertice, i_route, idNet, edge_usage, parser.gNumHTiles());

        for (int i = 0 ; i < x*y ; ++i) 
            vertice[i] -> set_pred(-1);

        int length = i_route.size() / 4;
        i_route.push_back(length);
        i_route.push_back(idNet);
        int count = 0;
        for (int i = i_route.size() - 1 ; i >= 0 ; --i) {
            kevin << i_route[i] << " ";
            count++;
            if (count == 2 || (count - 2) % 4 == 0)
                kevin << endl;
        }
    }
    return 0;
}