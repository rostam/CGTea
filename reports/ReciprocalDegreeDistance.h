 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_RECIPROCALDEGREEDISTANCE.JAVA_H
#define CGTEA_RECIPROCALDEGREEDISTANCE.JAVA_H

#include "ReportInterface.h"

class ReciprocalDegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Reciprocal Degree Distance";
    };
    string description() override {
        return "Reciprocal Degree Distance";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_RECIPROCALDEGREEDISTANCE.JAVA_H
