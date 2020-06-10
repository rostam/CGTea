 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_GIRTHSIZE.JAVA_H
#define CGTEA_GIRTHSIZE.JAVA_H

#include "ReportInterface.h"

class GraphGirthSize : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Graph Girth Size";
    };
    string description() override {
        return "Graph Girth Size";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_GIRTHSIZE.JAVA_H
