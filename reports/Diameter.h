 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DIAMETER.JAVA_H
#define CGTEA_DIAMETER.JAVA_H

#include "ReportInterface.h"

class GraphDiameter : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Graph Diameter";
    };
    string description() override {
        return "Graph Diameter";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_DIAMETER.JAVA_H
