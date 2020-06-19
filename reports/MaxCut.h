 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MAXCUT_H
#define CGTEA_MAXCUT_H

#include "ReportInterface.h"

class MaximumCut : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Maximum Cut";
    };
    string description() const override {
        return "Axproximate Maximum Cut In An Undirected Graph";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_MAXCUT_H
