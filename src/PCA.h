//
// Created by tadeze on 12/10/16.
//

#ifndef ADCVISUALIZATION_PCA_H
#define ADCVISUALIZATION_PCA_H
#include "armadillo"

class PCA {
public:
    PCA(const bool scaleData=false);
    void apply(const arma::mat & data,
    const size_t newDimension) const;
    ~PCA();
    bool ScaleData() const {return ScaleData;}
private:
    bool scaleData;

};


#endif //ADCVISUALIZATION_PCA_H
