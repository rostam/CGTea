 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WIENERPOLARITY.JAVA_H
#define CGTEA_WIENERPOLARITY.JAVA_H

#include "ReportInterface.h"

class WienerPolarity : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Wiener Polarity";
    };
    string description() override {
        return "Wiener Polarity";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WIENERPOLARITY.JAVA_H
