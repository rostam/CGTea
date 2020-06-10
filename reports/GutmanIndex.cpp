 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_GUTMANINDEX.JAVA_H
#define CGTEA_GUTMANINDEX.JAVA_H

#include "ReportInterface.h"

class GutmanIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Gutman Index";
    };
    string description() override {
        return "Gutman Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_GUTMANINDEX.JAVA_H
