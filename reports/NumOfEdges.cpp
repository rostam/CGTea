 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFEDGES.JAVA_H
#define CGTEA_NUMOFEDGES.JAVA_H

#include "ReportInterface.h"

class NumberofEdges : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of Edges";
    };
    string description() override {
        return "Number of edges in the Graph";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFEDGES.JAVA_H
