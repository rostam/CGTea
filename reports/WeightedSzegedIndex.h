 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WEIGHTEDSZEGEDINDEX_H
#define CGTEA_WEIGHTEDSZEGEDINDEX_H

#include "ReportInterface.h"

class WeightedSzegedIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Weighted Szeged Index";
    };
    string description() const override {
        return "Weighted Szeged Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WEIGHTEDSZEGEDINDEX_H
