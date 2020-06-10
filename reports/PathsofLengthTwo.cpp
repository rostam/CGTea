 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PATHSOFLENGTHTWO.JAVA_H
#define CGTEA_PATHSOFLENGTHTWO.JAVA_H

#include "ReportInterface.h"

class NumberofPathsofLength2 : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of Paths of Length 2";
    };
    string description() override {
        return "Number of Paths of Length 2";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_PATHSOFLENGTHTWO.JAVA_H
