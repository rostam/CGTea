 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_GUTMANINDEX_H
#define CGTEA_GUTMANINDEX_H

#include "ReportInterface.h"

class GutmanIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Gutman Index";
    };
    string description() const override {
        return "Gutman Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_GUTMANINDEX_H
