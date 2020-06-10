 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_REVISEDSZEGEDINDEX.JAVA_H
#define CGTEA_REVISEDSZEGEDINDEX.JAVA_H

#include "ReportInterface.h"

class RevisedSzegedIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Revised Szeged Index";
    };
    string description() override {
        return "Revised Szeged Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_REVISEDSZEGEDINDEX.JAVA_H
