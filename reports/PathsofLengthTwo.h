 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PATHSOFLENGTHTWO_H
#define CGTEA_PATHSOFLENGTHTWO_H

#include "ReportInterface.h"

class NumberofPathsofLength2 : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Number of Paths of Length 2";
    };
    string description() const override {
        return "Number of Paths of Length 2";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_PATHSOFLENGTHTWO_H
