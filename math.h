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
#include "main.h"
#include<armadillo>

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
double mean(vector<double> &datapoints)
{
    return 1.0;
 // return arma::mean(datapoints.begin(),datapoints.end());
}

vector<point> readPoints(const char* filename, char delim=',',bool header=true){
    ifstream fin(filename);
    string item;
    std::vector<point> values;
    if (header)  //if header available
        getline(fin, item);

    for (string line; getline(fin, line);) {
        istringstream in(line);
        point instance;
        int i=0;
        while (getline(in, item, delim)) {
          if(i==0)
            instance.x = atof(item.c_str());
            else if(i==1)
            instance.y = atof(item.c_str());
            else
            instance.z = atof(item.c_str());
            i++;
            //valueline.push_back(atof(item.c_str()));
        }
        values.push_back(instance);
        //values.push_back(valueline);
        //valueline.clear();
    }
    return values;
}


#endif //PROJECT4_MATH_H
