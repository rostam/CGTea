 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_CHROMATICNUMBER.JAVA_H
#define CGTEA_CHROMATICNUMBER.JAVA_H

#include "ReportInterface.h"

class ChromaticNumber : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Chromatic Number";
    };
    string description() override {
        return "The chromatic number of graph";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Coloring";
    };
};

#endif //CGTEA_CHROMATICNUMBER.JAVA_H
