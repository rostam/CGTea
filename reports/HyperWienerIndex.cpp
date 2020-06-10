 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_HYPERWIENERINDEX.JAVA_H
#define CGTEA_HYPERWIENERINDEX.JAVA_H

#include "ReportInterface.h"

class HyperWienerIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Hyper Wiener Index";
    };
    string description() override {
        return "Hyper Wiener Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_HYPERWIENERINDEX.JAVA_H
