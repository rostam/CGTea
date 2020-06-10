 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_EDGEDEGREE.JAVA_H
#define CGTEA_EDGEDEGREE.JAVA_H

#include "ReportInterface.h"

class EdgeDegree : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Edge Degree";
    };
    string description() override {
        return "For the edge u~v the edge degree is d(u)+d(v)-2.";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_EDGEDEGREE.JAVA_H
