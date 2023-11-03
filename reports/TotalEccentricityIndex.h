 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_TOTALECCENTRICITYINDEX_H
#define CGTEA_TOTALECCENTRICITYINDEX_H

#include "ReportInterface.h"

class TotaleccentrityIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Total eccentrity Index";
    };
    string description() const override {
        return "Total eccentrity Index";
    };
    string type() const override {
        return "double";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_TOTALECCENTRICITYINDEX_H
