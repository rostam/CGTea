//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_NUMCONNECTEDCOMPONENTS_H
#define CGTEA_NUMCONNECTEDCOMPONENTS_H

#include "ReportInterface.h"
#include <boost/graph/connected_components.hpp>

class NumConnectedComponents : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n == 0) return "0";
        std::vector<int> comp(n);
        int num = boost::connected_components(g, comp.data());
        return std::to_string(num);
    }
    string name() const override { return "Connected Components"; }
    string description() const override { return "Number of connected components"; }
    string type() const override { return "int"; }
    string category() const override { return "Connectivity"; }
};

#endif //CGTEA_NUMCONNECTEDCOMPONENTS_H
