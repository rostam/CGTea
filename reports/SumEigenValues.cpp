//
// Created by rostam on 19.06.20.
//

#include "SumEigenValues.h"
#include "EigenRelatedFunctions.h"

std::string SumEigenValues::report(const Graph& g) {
    std::tuple<double,double,double> t = EigenRelatedFunctions::eigen_values(g);
    return std::to_string(std::get<2>(t));
};
