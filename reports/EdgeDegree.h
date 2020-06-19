 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_EDGEDEGREE_H
#define CGTEA_EDGEDEGREE_H

#include "ReportInterface.h"

class EdgeDegree : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Edge Degree";
    };
    string description() const override {
        return "For the edge u~v the edge degree is d(u)+d(v)-2.";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_EDGEDEGREE_H
