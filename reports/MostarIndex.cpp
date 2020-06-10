 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_MOSTARINDEX.JAVA_H
#define CGTEA_MOSTARINDEX.JAVA_H

#include "ReportInterface.h"

class MostarIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Mostar Index";
    };
    string description() override {
        return "Mostar Index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_MOSTARINDEX.JAVA_H
