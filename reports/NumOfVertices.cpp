 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFVERTICES.JAVA_H
#define CGTEA_NUMOFVERTICES.JAVA_H

#include "ReportInterface.h"

class NumberofVertices : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of Vertices";
    };
    string description() override {
        return "Number of vertices in the Graph";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFVERTICES.JAVA_H
