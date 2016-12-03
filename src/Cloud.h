//
// Created by tadeze on 12/2/16.
//

#ifndef PROJECT4_CLOUD_H
#define PROJECT4_CLOUD_H
#include "armadillo"

struct CloudCenter{
    float centerX,centerY,centerZ;
    float radiusX,radiusY,radiusZ;
};
class Cloud{
    //std::vector<double> centroids;
    std::vector<int> observations;
    float centerX,centerY,centerZ;

public:
    Cloud();
    virtual ~Cloud();
    Cloud(std::vector<int> &index,std::vector<std::vector<double> > &points);
    std::vector<double> meanRadius();
    std::vector<double> covariance();


    //Point mean(std::vector<Point> &points);
    //std::vector<double> radiusXYZ();
};

#endif //PROJECT4_CLOUD_H
