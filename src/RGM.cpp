//
// Created by tadeze on 12/2/16.
//

#include "RGM.h"
arma::mat RGM::vec2mat(std::vector<std::vector<double> >&vec){
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
arma::vec RGM::getEigenValues(arma::mat M) {
    return arma::eig_sym(M);
}

arma::mat RGM::covariance() {

    arma::mat cov = arma::cov(data);
    return cov;

}

cloudpp RGM::radiusXYZ() {
    cloudpp cldpp;
    arma::vec eigenV = getEigenValues(covariance());
    float chisqr =2.4477; //95% percentage
     arma::mat mn = arma::mean(data);
    cldpp.x = (float)mn[0];cldpp.y = (float)mn[1];cldpp.z= (float)mn[2];
    //Calculate the size of the minor and major axes
    cldpp.radiusX=(float)chisqr*sqrt(eigenV[0]);
    cldpp.radiusY=(float)chisqr*sqrt(eigenV[1]);
    cldpp.radiusZ=(float)chisqr*sqrt(eigenV[2]);
    return cldpp;

}