//
// Created by tadeze on 11/28/16.
//

#ifndef PROJECT4_MATH_H
#define PROJECT4_MATH_H
//#include "main.h"

#include<fstream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<algorithm>
//#include "main.h"
//#include "geometry.h"
#include "armadillo"
using namespace std;

//using namespace arma;
/*
double median(std::vector<double> &observation){

    double meddd = std::sort(observation.begin(),observation.end());
    return meddd;

}*/
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

vector<double> means(vector<vector<double> > points)
{
double x=0.0,y=0.0,z=0.0;
    vector<double> xyz;
    int i=0;
    for(i=0;i<points.size();i++)
    {

        x+=points[i][0];
        y+=points[i][1];
        z+=points[i][2];
    }
    xyz.push_back(x/i);
    xyz.push_back(y/i);
    xyz.push_back(z/i);
    return xyz;

}




/*
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
*/

//std::vector<point> readPoints(const char* filename, char delim=',',bool header=true);






#endif //PROJECT4_MATH_H
