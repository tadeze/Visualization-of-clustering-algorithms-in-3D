//
// Created by tadeze on 12/2/16.
//

#ifndef PROJECT4_CLOUD_H
#define PROJECT4_CLOUD_H
#include "armadillo"
class Cloud{
    std::vector<double> centroids;
    std::vector<int> observations;

public:
    Cloud(){};
    std::vector<double> clusterRadius();
    std::vector<double> covariance();

    //Point mean(std::vector<Point> &points);
    //std::vector<double> radiusXYZ();
};

#endif //PROJECT4_CLOUD_H
