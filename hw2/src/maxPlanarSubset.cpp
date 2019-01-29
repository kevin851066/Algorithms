#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

using namespace std;

typedef vector< pair<int, int> > VP;

void trace(int , int , int* , bool**, VP&);

int main(int argc, char *argv[]) {
    ifstream infile;
    infile.open(argv[1]);
    // read the first line of file (vertices)
    int vertices = 0;   
    infile >> vertices;
    int chords = vertices / 2;
    // 2D dynamic array to save MIS
    int** MIStable = new int*[2 * chords]();
    // j from 1 to (2 * chords - 1), i from 0 to (j -1)
    bool** traceMat = new bool*[2 * chords]();
    for (int i = 0; i < 2 * chords; ++i) {
        MIStable[i] = new int[2 * chords]();
        traceMat[i] = new bool[2 * chords]();
    }
    // let the 0 index element equal to 4, the 4 index element equal to 0
    int ChordTable[vertices];
    // read the rest of file ()
    for ( int i = 0 ; i < chords ; ++i ) {
        int v1 = 0;
        int v2 = 0;
        infile >> v1 >> v2;
        ChordTable[v1] = v2;
        ChordTable[v2] = v1;
    }

    for ( int j = 0 ; j < 2 * chords ; ++j ) {
        for ( int i = 0 ; i < j ; ++i ) {
            if (i >= j)
                continue;
            else {  // i < j
                int k = ChordTable[j];
                if (i <= k && k < j) {  
                    if (i == k) { // case 3
                        MIStable[i][j] = MIStable[i + 1][j - 1] + 1;
                        traceMat[i][j] = true;
                    }
                    else { // compare case1 and case2
                        if ( (MIStable[i][k - 1] + 1 + MIStable[k + 1][j - 1]) > MIStable[i][j - 1] ) {
                            MIStable[i][j] = MIStable[i][k - 1] + 1 + MIStable[k + 1][j - 1];
                            traceMat[i][j] = true;
                        }
                        else 
                            MIStable[i][j] = MIStable[i][j - 1];
                    }
                }
                else  // case 1 
                    MIStable[i][j] = MIStable[i][j - 1]; 
            }
        }
    }

    VP MISpair;
    MISpair.reserve(MIStable[0][2 * chords - 1]);

    trace(0, 2 * chords - 1, ChordTable, traceMat, MISpair);
    // end of file
    sort(MISpair.begin(), MISpair.end());
    
    // output
    fstream kevin;
    kevin.open(argv[2], ios::out);
    kevin << MIStable[0][2 * chords - 1] << endl;
    for (int i = 0; i < MISpair.size(); i++) 
        kevin << MISpair[i].first << " " << MISpair[i].second << endl;

    int done;
    infile >> done;
    if (!done)
        return 0;
}

void trace(int i, int j, int* ChordT, bool** Tmat, VP& vp) {
    if (i < j && i >= 0 && j >= 0) {
        int k = ChordT[j];
        if (i <= k && k < j) {
            if (i == k) {
                vp.push_back(make_pair(k, j));
                trace(i + 1, j - 1, ChordT, Tmat, vp);
            }
            else {
                if (Tmat[i][j]) {
                    vp.push_back(make_pair(k, j));
                    trace(i, k - 1, ChordT, Tmat, vp);
                    trace(k + 1, j - 1, ChordT, Tmat, vp);
                }
                else 
                    trace(i, j - 1, ChordT, Tmat, vp);
            }
        }
        else 
            trace(i, j - 1, ChordT, Tmat, vp);
    }
}