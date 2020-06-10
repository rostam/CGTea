 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFINDSETS.JAVA_H
#define CGTEA_NUMOFINDSETS.JAVA_H

#include "ReportInterface.h"

class Numberofindependentsetsplusemptyset : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of independent sets plus empty set";
    };
    string description() override {
        return "Number of independent sets in the Graph";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFINDSETS.JAVA_H
