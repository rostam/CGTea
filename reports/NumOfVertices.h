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
    string name() const override {
        return "Number of vertices";
    };
    string description() const override {
        return "Number of vertices";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFVERTICES_H
