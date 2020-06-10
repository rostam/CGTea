 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_TOTALECCENTRICITYINDEX.JAVA_H
#define CGTEA_TOTALECCENTRICITYINDEX.JAVA_H

#include "ReportInterface.h"

class TotaleccentrityIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Total eccentrity Index";
    };
    string description() override {
        return "Total eccentrity Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_TOTALECCENTRICITYINDEX.JAVA_H
