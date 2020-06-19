 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFTRIANGLES_H
#define CGTEA_NUMOFTRIANGLES_H

#include "ReportInterface.h"

class NumberOfTriangles : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Number Of Triangles";
    };
    string description() const override {
        return "Number Of Triangles";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFTRIANGLES_H
