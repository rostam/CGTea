 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_CHROMATICNUMBER_H
#define CGTEA_CHROMATICNUMBER_H

#include "ReportInterface.h"

class ChromaticNumber : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Chromatic Number";
    };
    string description() const override {
        return "The chromatic number of graph";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Coloring";
    };
};

#endif //CGTEA_CHROMATICNUMBER_H
