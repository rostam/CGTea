 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MAXCUT.JAVA_H
#define CGTEA_MAXCUT.JAVA_H

#include "ReportInterface.h"

class MaximumCut : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Maximum Cut";
    };
    string description() override {
        return "Axproximate Maximum Cut In An Undirected Graph";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_MAXCUT.JAVA_H
