 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFQUADRANGLE_H
#define CGTEA_NUMOFQUADRANGLE_H

#include "ReportInterface.h"

class numberofquadrangle : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "number of quadrangle";
    };
    string description() const override {
        return "number of quadrangle";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFQUADRANGLE_H
