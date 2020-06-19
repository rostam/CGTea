 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MOSTARINDEX_H
#define CGTEA_MOSTARINDEX_H

#include "ReportInterface.h"

class MostarIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Mostar Index";
    };
    string description() const override {
        return "Mostar Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_MOSTARINDEX_H
