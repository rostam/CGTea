 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFTRIANGLES.JAVA_H
#define CGTEA_NUMOFTRIANGLES.JAVA_H

#include "ReportInterface.h"

class NumberOfTriangles : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Number Of Triangles";
    };
    string description() override {
        return "Number Of Triangles";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFTRIANGLES.JAVA_H
