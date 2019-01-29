#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include "parser.h"
#include "parser.cpp"
#include <fstream>
#include <math.h>

typedef vector< pair<string, int> > VP;
void heapify(VP&, int, int);
void build(VP&);

int main( int argc, char** argv )
{
    // Declare the functional objects
    AlgParser p;
    AlgTimer t;
    // Pass the arguement 1 as the input file name
    p.Parse( argv[1] );
    // Start timer
    t.Begin();

    VP vp;
    vp.reserve(p.QueryTotalStringCount());

    for ( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) {
        vp.push_back(make_pair(p.QueryString(i), i+1)); } 

    build(vp);
    // int length = vp.size();
    for (int i = vp.size()-1 ; i > 0 ; i--) {
        pair<string, int> buf = vp[i];
        vp[i] = vp[0];
        vp[0] = buf;
        heapify(vp, 0, i);
    }
    
    fstream kevin;
    
    kevin.open(argv[2], ios::out);
    kevin<<p.QueryTotalStringCount()<<endl;
    for ( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) {
        kevin<<vp[i].first<<" "<<vp[i].second<<endl; }
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
    // char c = getchar();
    return 1;
}

void heapify(VP& ex, int i, int length) {  //i starts from 0
    int l = 2*i+1, r = 2*i+2, largest = -1;
    if (l <= length-1 && ex[l] > ex[i]) 
        largest = l;
    else 
        largest = i;    
    if (r <= length-1 &&  ex[r]> ex[largest]) 
        largest = r;
    if (largest != i) {
        pair<string, int> buf = ex[i];
        ex[i] = ex[largest];
        ex[largest] = buf;
        heapify(ex, largest, length);
        // if (lr == 1)
        //     heapify(ex, 2*i+1, length);
        // else if (lr == 2)
        //     heapify(ex, 2*i+2, length);
    }
}

void build(VP& ex) {
    for (int i = floor(ex.size()/2) ; i >= 0 ; i--) 
        heapify(ex, i, ex.size()); 
}