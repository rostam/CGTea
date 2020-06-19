 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_SZEGEDINDEX_H
#define CGTEA_SZEGEDINDEX_H

#include "ReportInterface.h"

class SzegedIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Szeged Index";
    };
    string description() const override {
        return "Szeged Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_SZEGEDINDEX_H
