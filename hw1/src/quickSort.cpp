#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "parser.h"
#include <stdio.h>
#include "parser.cpp"
#include <fstream>

typedef vector< pair<string, int> > VP;
int partition(VP&, int, int);
void quicksort(VP&, int, int);

int main( int argc, char** argv ) {
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
    
    quicksort(vp,0,p.QueryTotalStringCount()-1);

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

int partition(VP& ex, int p, int r) {
    // srand( time(NULL) );
    // pair<string, int> x = ex[(rand()%(r-p+1))+p];
    pair<string, int> x = ex[p];
    int i = p;
    int j = r;
    while (true) {
        while (ex[j] > x) 
            j-=1;
        while (ex[i] < x)
            i+=1;
        if (i<j) {
            pair<string, int> buf = ex[i];
            ex[i] = ex[j];
            ex[j] = buf;
        }
        else    
            return j;
    }
}
void quicksort(VP& ex, int p, int r) {
    // cout<<"p: "<<p<<"r: "<<r<<endl;
    if (p<r) {
        int q = partition(ex,p,r);
        // cout<<"q: "<<q<<endl;
        quicksort(ex,p,q);
        quicksort(ex,q+1,r);
    }
}
