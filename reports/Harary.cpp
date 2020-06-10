 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_HARARY.JAVA_H
#define CGTEA_HARARY.JAVA_H

#include "ReportInterface.h"

class HararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Harary Index";
    };
    string description() override {
        return "Harary Index";
    };
    string type() override {
        return "double";
    };
    string category() override {
        return "Topological Indices";
    };
};

#endif //CGTEA_HARARY.JAVA_H
