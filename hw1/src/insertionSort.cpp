#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "parser.h"
#include "parser.cpp"
#include <fstream>

using namespace std;

int main( int argc, char** argv) 
{
    // Declare the functional objects
    AlgParser p;
    AlgTimer t;

    // Pass the arguement 1 as the input file name
    p.Parse( argv[1] );
    // Start timer
    t.Begin();

    typedef vector< pair<string, int> > VP;
    VP vp;
    vp.reserve(p.QueryTotalStringCount());

    for ( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) {
        vp.push_back(make_pair(p.QueryString(i), i+1)); }  

    for ( int i = 1 ; i < p.QueryTotalStringCount() ; i++ ) {
        pair<string, int> key = vp[i];
        int j = i-1;
        while ( j >= 0 && vp[j] > key ) {
            vp[j+1] = vp[j];
            j = j-1;
        }
        vp[j+1] = key;
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