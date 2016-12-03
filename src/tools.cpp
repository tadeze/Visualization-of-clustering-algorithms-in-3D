//
// Created by tadeze on 12/1/16.
//

#include "tools.h"
//using namespace std;
//using namespace std;

//using namespace arma;
/*
double median(std::vector<double> &observation){

    double meddd = std::sort(observation.begin(),observation.end());
    return meddd;

}*/
std::vector<std::vector<double> > readcsv(const char* filename, char delim ,
                                bool header) {
    std::vector < std::vector<double> > values;
    std::vector<double> valueline;
    std::ifstream fin(filename);
    std::string item;
    if (header)  //if header available
        getline(fin, item);

    for (std::string line; getline(fin, line);) {
        std::istringstream in(line);
        while (getline(in, item, delim)) {
            valueline.push_back(atof(item.c_str()));
        }
        values.push_back(valueline);
        valueline.clear();
    }
    return values;
}

std::vector<double> means(std::vector<std::vector<double> > points)
{
    double x=0.0,y=0.0,z=0.0;
    std::vector<double> xyz;
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


float max(float a, float b)
{
    return a>b?a:b;
}
float medianR(std::vector<double> &observations)
{
    float dist = 0.0;
    std::vector<double> medd;
    for(int i=0;i<observations.size();i++)
    {
        dist +=observations[i];
    }

    float mn = dist/(float)observations.size();
    return mn;
}

cloudpp radiusXYZ(std::vector<int> &cluster, std::vector<std::vector<double> > &points)
{
    cloudpp cpp;
    float x=0.0,y=0.0,z=0.0;
    cpp.radiusX=0;cpp.radiusY=0.0;cpp.radiusZ=0.0;
    int len = cluster.size();

    for(int i=0;i<len;i++)
    {
        x+=points[cluster[i]][0];
        y+=points[cluster[i]][1];
        z+=points[cluster[i]][2];
    }
    cpp.x = x/len; cpp.y = y/len;cpp.z = z/len;
    std::vector<double> distX,distY,distZ;
    for(int i=0;i<len;i++)
    {
        distX.push_back(points[cluster[i]][0]);//-cpp.x));
        distY.push_back(points[cluster[i]][1]);//-cpp.y));
        distZ.push_back(points[cluster[i]][2]);//-cpp.z));

//        cpp.radiusX = cpp.radiusX + abs(points[cluster[i]][0]-cpp.x);
//        cpp.radiusY = cpp.radiusY + abs(points[cluster[i]][1]-cpp.y);
//        cpp.radiusZ = cpp.radiusZ + abs(points[cluster[i]][2]-cpp.z);

    }

    cpp.radiusX = medianR(distX);
    cpp.radiusY = medianR(distY);
    cpp.radiusZ = medianR(distZ);
    return cpp;
}
