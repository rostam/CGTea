 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFQUADRANGLE.JAVA_H
#define CGTEA_NUMOFQUADRANGLE.JAVA_H

#include "ReportInterface.h"

class numberofquadrangle : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "number of quadrangle";
    };
    string description() override {
        return "number of quadrangle";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFQUADRANGLE.JAVA_H
