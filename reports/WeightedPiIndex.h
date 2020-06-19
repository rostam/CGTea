 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WEIGHTEDPIINDEX_H
#define CGTEA_WEIGHTEDPIINDEX_H

#include "ReportInterface.h"

class WeightedPIIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Weighted PI Index";
    };
    string description() const override {
        return "Weighted PI Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WEIGHTEDPIINDEX_H
