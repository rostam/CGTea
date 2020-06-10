 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_ADDITIVEHARARY.JAVA_H
#define CGTEA_ADDITIVEHARARY.JAVA_H

#include "ReportInterface.h"

class AdditiveHararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "AdditiveHarary Index";
    };
    string description() override {
        return "AdditiveHarary Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_ADDITIVEHARARY.JAVA_H
