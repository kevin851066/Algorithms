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

typedef vector< pair<string, int> > VP;

void merge(VP& ex, int p, int q, int r) {
    int n1 = q-p+1;
    // cout<<"n1: "<<n1<<endl;
    int n2 = r-q;
    // cout<<"n2: "<<n2<<endl;
    VP l;
    VP rr;
    l.reserve(n1);
    rr.reserve(n2);
    // cout<<"-----START-----"<<endl;
    for (int i = 0; i < n1; i++) {
        l.push_back(ex[p+i]); }
    // cout<<"-----STAGE1-----"<<endl;
    for (int j = 0; j < n2; j++) {  
        rr.push_back(ex[q+j+1]); }
    // cout<<"-----STAGE2-----"<<endl;
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++) {
        if (i >= n1 ) {
            ex[k] = rr[j];
            j+=1;
        }
        else if (j >= n2 ) {
            ex[k] = l[i];
            i+=1;
        }
        else if (l[i] < rr[j]) {
            ex[k] = l[i];
            i+=1;
        }
        else {
            ex[k] = rr[j];
            j+=1;
        }
        // cout<<"k: "<<k<<endl;
    }
    // cout<<"-----COMPLETE-----"<<endl;
}

void mergeSort(VP& ex, int p, int r) {
    if (p < r) {
        int q = (p+r)/2;
        // cout<<"p: "<<p<<" "<<"q: "<<q<<" "<<"r: "<<r<<endl;
        // cout<<"-----ROUND1------"<<endl;
        // cout<<"f: "<<p<<" "<<"l: "<<q<<endl;
        mergeSort(ex, p, q);
        // cout<<"-----ROUND2------"<<endl;
        // cout<<"f: "<<q+1<<" "<<"l: "<<r<<endl;
        mergeSort(ex, q+1, r);
        // cout<<"------MERGE------"<<endl;
        // cout<<"p: "<<p<<" "<<"q: "<<q<<" "<<"r: "<<r<<endl;
        merge(ex, p, q, r);
    }
}

// void mergeSort(VP, int, int);
// void merge(VP, int, int, int);

int main( int argc, char** argv) 
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

    mergeSort(vp, 0, p.QueryTotalStringCount()-1);

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

