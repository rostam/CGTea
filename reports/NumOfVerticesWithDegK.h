 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFVERTICESWITHDEGK_H
#define CGTEA_NUMOFVERTICESWITHDEGK_H

#include "ReportInterface.h"

class NumberofVerticeswithDegk : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Number of Vertices with Deg k";
    };
    string description() const override {
        return "Number of vertices in the Graph which degrees are k";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFVERTICESWITHDEGK_H
