//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFEDGES_H
#define CGTEA_NUMOFEDGES_H

#include "ReportInterface.h"

class NumOfEdges : public ReportInterface{
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of edges";
    };
    string description() override {
        return "Number of edges";
    };
};

#endif //CGTEA_NUMOFEDGES_H
