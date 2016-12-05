//
// Created by tadeze on 12/2/16.
//

#ifndef PROJECT4_KMEAN_H
#define PROJECT4_KMEAN_H
#include "Cloud.h"
/*
namespace {
    arma::mat generateData(int N, int d ,int mu)
    {
        arma::mat dd(N,d,arma::fill::fill_randn(2,0));

    }
}

*/

class Kmean {
std::vector<Cloud> clouds;
    int K;
public:
    Kmean(){};
    arma::mat vec2mat(std::vector<std::vector<double> >&vec);
    double getDistance(arma::rowvec a, arma::rowvec b);
    double nearestCenter(std::vector<arma::rowvec>& centroids, arma::rowvec pt);
    std::vector<std::vector<std::vector<int> > > kmeans(std::vector<std::vector<double> > &input_vectors, int K);
   // void kmeanC(std::vector<std::vector<double> >&input_vectors, int K);
    double distortion(arma::mat data, std::vector<std::vector<int> >& cluster, std::vector<arma::rowvec>& centroids);

};


#endif //PROJECT4_KMEAN_H
