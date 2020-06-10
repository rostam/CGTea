 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_CONNECTIVITYECCENTRICITYINDEX.JAVA_H
#define CGTEA_CONNECTIVITYECCENTRICITYINDEX.JAVA_H

#include "ReportInterface.h"

class CEIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "CE Index";
    };
    string description() override {
        return "CE Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_CONNECTIVITYECCENTRICITYINDEX.JAVA_H
