 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_RECIPROCALDEGREEDISTANCE_H
#define CGTEA_RECIPROCALDEGREEDISTANCE_H

#include "ReportInterface.h"

class ReciprocalDegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Reciprocal Degree Distance";
    };
    string description() const override {
        return "Reciprocal Degree Distance";
    };
    string type() const override {
        return "double";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_RECIPROCALDEGREEDISTANCE_H
