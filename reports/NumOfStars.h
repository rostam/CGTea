 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFSTARS_H
#define CGTEA_NUMOFSTARS_H

#include "ReportInterface.h"

class NumberofStars : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Number of Stars";
    };
    string description() const override {
        return "Number of Stars";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFSTARS_H
