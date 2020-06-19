 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DEGREEDISTANCE_H
#define CGTEA_DEGREEDISTANCE_H

#include "ReportInterface.h"

class DegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Degree Distance";
    };
    string description() const override {
        return "Degree Distance";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_DEGREEDISTANCE_H
