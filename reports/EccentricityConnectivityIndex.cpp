 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_ECCENTRICITYCONNECTIVITYINDEX.JAVA_H
#define CGTEA_ECCENTRICITYCONNECTIVITYINDEX.JAVA_H

#include "ReportInterface.h"

class ECIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "EC Index";
    };
    string description() override {
        return "EC Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_ECCENTRICITYCONNECTIVITYINDEX.JAVA_H
