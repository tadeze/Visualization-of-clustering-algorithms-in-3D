//
// Created by tadeze on 12/2/16.
//

#include "kmean.h"



arma::mat Kmean::vec2mat(std::vector<std::vector<double> >&vec){
    int rows = vec.size();

    int cols = vec[0].size();
    arma::mat A(rows,cols);
    for(int i = 0; i<rows; i++){
        for(int j=0; j<cols; j++){
            A(i, j) = vec[i][j];
        }
    }
    return A;
}

double Kmean::getDistance(arma::rowvec a, arma::rowvec b) {
    arma::rowvec temp = a - b;
    return arma::norm(temp, 2);
}
double Kmean::distortion(arma::mat data, std::vector<std::vector<int> > &cluster,
                         std::vector<arma::rowvec> &centroids){
    int nSamples = data.n_rows;
    int nDim = data.n_cols;
    double SumDistortion = 0.0;
    for(int i = 0; i < cluster.size(); i++){
        for(int j = 0; j < cluster[i].size(); j++){
            double temp = getDistance(data.row(cluster[i][j]), centroids[i]);
            SumDistortion += temp;
        }
    }
    return SumDistortion;
}
double Kmean::nearestCenter(std::vector<arma::rowvec>& centroids, arma::rowvec pt){

    double minDistance = 0;
    int minLabel = 0;
    for(int i=0; i<centroids.size(); i++){
        double tempDistance = getDistance(centroids[i], pt);
        if(i == 0|| tempDistance < minDistance){
            minDistance = tempDistance;
            minLabel = i;
        }
    }
    return minLabel;

}

std::vector<std::vector<std::vector<int> > > Kmean::kmeans(std::vector<std::vector<double> >&input_vectors, int K){

    arma::mat data = vec2mat(input_vectors);
    int nSamples = data.n_rows;
    int nDim = data.n_cols;
    //randomly select k samples to initialize k centroid
    std::vector<arma::rowvec> centroids;
    for(int k = 0; k < K; k ++){
        int rand_int = rand() % nSamples;
        centroids.push_back(data.row(rand_int));
    }

    std::vector<std::vector<std::vector<int> > > clusterCollection;

    //iteratively find better centroids
    std::vector<std::vector<int> > cluster;
    for(int k = 0; k < K; k ++){
        std::vector<int > vectemp;
        cluster.push_back(vectemp);

    }

    int counter = 0;
    while(1){
        for(int k = 0; k < K; k ++){
            cluster[k].clear();
        }
        bool converge = true;
        //for every sample, find which cluster it belongs to,
        //by comparing the distance between it and each clusters' centroid.
        for(int m = 0; m < nSamples; m++){
            int which = nearestCenter(centroids, data.row(m));
            cluster[which].push_back(m);
        }
        //for every cluster, re-calculate its centroid.
        for(int k = 0; k < K; k++){
            int cluster_size = cluster[k].size();
            arma::rowvec vectemp = arma::zeros<arma::rowvec>(nDim);
            for(int i = 0; i < cluster_size; i++){
                vectemp = vectemp + data.row(cluster[k][i]) / (double)cluster_size;
            }
            if(getDistance(centroids[k], vectemp) >= 1e-6) converge = false;
            centroids[k] = vectemp;
        }
        if(converge) break;
        ++counter;
        clusterCollection.push_back(cluster);
        //std::cout<<counter<<std::endl;
    }
    return clusterCollection;
  //double dist = distortion(data, cluster, centroids);

    //return dist;

}

/*
std::vector<cloud> Kmean::kmeanC(std::vector<std::vector<double> >&input_vectors, int K){

    arma::mat data = vec2mat(input_vectors);
    int nSamples = data.n_rows;
    int nDim = data.n_cols;
    //randomly select k samples to initialize k centroid
    std::vector<arma::rowvec> centroids;
    for(int k = 0; k < K; k ++){
        int rand_int = rand() % nSamples;
        centroids.push_back(data.row(rand_int));
    }

    //iteratively find better centroids
    std::vector<std::vector<int> > cluster;
    for(int k = 0; k < K; k ++){
        std::vector<int > vectemp;
        cluster.push_back(vectemp);

    }

    int counter = 0;
    while(1){
        for(int k = 0; k < K; k ++){
            cluster[k].clear();
        }
        bool converge = true;
        //for every sample, find which cluster it belongs to,
        //by comparing the distance between it and each clusters' centroid.
        for(int m = 0; m < nSamples; m++){
            int which = nearestCenter(centroids, data.row(m));
            cluster[which].push_back(m);
        }
        //for every cluster, re-calculate its centroid.
        for(int k = 0; k < K; k++){
            int cluster_size = cluster[k].size();
            arma::rowvec vectemp = arma::zeros<arma::rowvec>(nDim);
            for(int i = 0; i < cluster_size; i++){
                vectemp = vectemp + data.row(cluster[k][i]) / (double)cluster_size;
            }
            if(getDistance(centroids[k], vectemp) >= 1e-6) converge = false;
            centroids[k] = vectemp;
        }
        if(converge) break;
        ++counter;
        //std::cout<<counter<<std::endl;
    }
std::vector<cloud> clouds;
    for(int k=0;k<K;k++)
    {
        cloud cld ;
    }


}*/