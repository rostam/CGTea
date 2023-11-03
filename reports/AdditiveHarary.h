 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_ADDITIVEHARARY_H
#define CGTEA_ADDITIVEHARARY_H

#include "ReportInterface.h"

class AdditiveHararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "AdditiveHarary Index";
    };
    string description() const override {
        return "AdditiveHarary Index";
    };
    string type() const override {
        return "double";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_ADDITIVEHARARY_H
