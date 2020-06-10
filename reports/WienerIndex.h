 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WIENERINDEX.JAVA_H
#define CGTEA_WIENERINDEX.JAVA_H

#include "ReportInterface.h"

class WienerIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Wiener Index";
    };
    string description() override {
        return "Wiener Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WIENERINDEX.JAVA_H
