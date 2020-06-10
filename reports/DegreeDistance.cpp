 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DEGREEDISTANCE.JAVA_H
#define CGTEA_DEGREEDISTANCE.JAVA_H

#include "ReportInterface.h"

class DegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Degree Distance";
    };
    string description() override {
        return "Degree Distance";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_DEGREEDISTANCE.JAVA_H
