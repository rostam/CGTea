 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WEIGHTEDSZEGEDINDEX.JAVA_H
#define CGTEA_WEIGHTEDSZEGEDINDEX.JAVA_H

#include "ReportInterface.h"

class WeightedSzegedIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Weighted Szeged Index";
    };
    string description() override {
        return "Weighted Szeged Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WEIGHTEDSZEGEDINDEX.JAVA_H
