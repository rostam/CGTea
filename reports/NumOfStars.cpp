 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFSTARS.JAVA_H
#define CGTEA_NUMOFSTARS.JAVA_H

#include "ReportInterface.h"

class NumberofStars : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of Stars";
    };
    string description() override {
        return "Number of Stars";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFSTARS.JAVA_H
