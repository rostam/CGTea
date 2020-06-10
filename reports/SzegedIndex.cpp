 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_SZEGEDINDEX.JAVA_H
#define CGTEA_SZEGEDINDEX.JAVA_H

#include "ReportInterface.h"

class SzegedIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Szeged Index";
    };
    string description() override {
        return "Szeged Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_SZEGEDINDEX.JAVA_H
