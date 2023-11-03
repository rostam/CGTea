 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MAXOFINDSETS_H
#define CGTEA_MAXOFINDSETS_H

#include "ReportInterface.h"

class Numberofindependentsetsplusemptyset : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Number of independent sets plus empty set";
    };
    string description() const override {
        return "Number of independent sets in the Graph";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_MAXOFINDSETS_H
