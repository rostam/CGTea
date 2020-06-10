 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFVERTICESWITHDEGK.JAVA_H
#define CGTEA_NUMOFVERTICESWITHDEGK.JAVA_H

#include "ReportInterface.h"

class NumberofVerticeswithDegk : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number of Vertices with Deg k";
    };
    string description() override {
        return "Number of vertices in the Graph which degrees are k";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFVERTICESWITHDEGK.JAVA_H
