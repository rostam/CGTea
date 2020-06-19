 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PIINDEX_H
#define CGTEA_PIINDEX_H

#include "ReportInterface.h"

class PIIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "PI Index";
    };
    string description() const override {
        return "PI Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_PIINDEX_H
