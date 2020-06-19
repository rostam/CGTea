//
// Created by rostam on 19.06.20.
//

#include "MaxEigenValue.h"
#include "EigenRelatedFunctions.h"

std::string MaxEigenValue::report(const Graph& g) {
    std::tuple<double,double,double> t = EigenRelatedFunctions::eigen_values(g);
    return std::to_string(std::get<0>(t));
}
