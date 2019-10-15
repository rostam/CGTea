//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFVERTICES_H
#define CGTEA_NUMOFVERTICES_H

#include "ReportInterface.h"

class NumOfVertices : public ReportInterface{
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of vertices";
    };
    string description() override {
        return "Number of vertices";
    };
};

#endif //CGTEA_NUMOFVERTICES_H
