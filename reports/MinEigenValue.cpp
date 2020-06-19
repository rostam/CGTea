//
// Created by rostam on 19.06.20.
//

#include "MinEigenValue.h"
#include "EigenRelatedFunctions.h"

string report(const Graph& g) override {
    std::tuple<double,double,double> t = EigenRelatedFunctions::eigen_values(g);
    return std::to_string(std::get<1>(t));
};