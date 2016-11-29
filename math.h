//
// Created by tadeze on 11/28/16.
//

#ifndef PROJECT4_MATH_H
#define PROJECT4_MATH_H
#include<fstream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
//#include "geometry.h"
//#include<armadillo>

//using namespace arma;
using namespace std;

vector<vector<double> > readcsv(const char* filename, char delim = ',',
                                bool header = true) {
    vector < vector<double> > values;
    vector<double> valueline;
    ifstream fin(filename);
    string item;
    if (header)  //if header available
        getline(fin, item);

    for (string line; getline(fin, line);) {
        istringstream in(line);
        while (getline(in, item, delim)) {
            valueline.push_back(atof(item.c_str()));
        }
        values.push_back(valueline);
        valueline.clear();
    }
    return values;
}
/*
void readPoints(const char* filename,vector<Point> &points, char delim=',',bool header=true){
    ifstream fin(filename);
    string item;
    if (header)  //if header available
        getline(fin, item);

    for (string line; getline(fin, line);) {
        istringstream in(line);
        Point instance;
        while (getline(in, item, delim)) {

            valueline.push_back(atof(item.c_str()));
        }
        values.push_back(valueline);
        valueline.clear();
    }
    return values;
}
*/

#endif //PROJECT4_MATH_H
