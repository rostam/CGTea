 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MULTIPLICATIVEHARARY_H
#define CGTEA_MULTIPLICATIVEHARARY_H

#include "ReportInterface.h"

class MultiplicativeHararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "MultiplicativeHarary Index";
    };
    string description() const override {
        return "MultiplicativeHarary Index";
    };
    string type() const override {
        return "double";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_MULTIPLICATIVEHARARY_H
