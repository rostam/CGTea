 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PIINDEX.JAVA_H
#define CGTEA_PIINDEX.JAVA_H

#include "ReportInterface.h"

class PIIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "PI Index";
    };
    string description() override {
        return "PI Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_PIINDEX.JAVA_H
