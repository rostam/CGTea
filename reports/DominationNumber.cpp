 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DOMINATIONNUMBER.JAVA_H
#define CGTEA_DOMINATIONNUMBER.JAVA_H

#include "ReportInterface.h"

class GraphDominationNumber : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Graph Domination Number";
    };
    string description() override {
        return "Graph Domination Number";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_DOMINATIONNUMBER.JAVA_H
