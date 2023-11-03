 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DOMINATIONNUMBER_H
#define CGTEA_DOMINATIONNUMBER_H

#include "ReportInterface.h"

class GraphDominationNumber : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Graph Domination Number";
    };
    string description() const override {
        return "Graph Domination Number";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_DOMINATIONNUMBER_H
