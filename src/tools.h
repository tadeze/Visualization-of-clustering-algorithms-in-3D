//
// Created by tadeze on 11/28/16.
//

#ifndef PROJECT4_TOOLS_H
#define PROJECT4_TOOLS_H
//#include "main.h"

#include<fstream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<algorithm>
#include "armadillo"
enum rAvg{
    MEAN,
    MEDIAN,
    MAX
};

struct cloudpp{
    float x,y,z;
    float radiusX,radiusY,radiusZ;
};
std::vector<std::vector<double> > readcsv(const char* filename, char delim,
                                bool header );

std::vector<double> means(std::vector<std::vector<double> > points);

arma::mat generateSyntheticData(int nsample,int ncluster);

float max(float a, float b);
float medianR(std::vector<double> &observations);

cloudpp radiusXYZ(std::vector<int> &cluster, std::vector<std::vector<double> > &points,rAvg distType);

#endif //PROJECT4_MATH_H
