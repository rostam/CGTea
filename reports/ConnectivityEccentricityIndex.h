 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_CONNECTIVITYECCENTRICITYINDEX_H
#define CGTEA_CONNECTIVITYECCENTRICITYINDEX_H

#include "ReportInterface.h"

class CEIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "CE Index";
    };
    string description() const override {
        return "CE Index";
    };
    string type() const override {
        return "double";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_CONNECTIVITYECCENTRICITYINDEX_H
