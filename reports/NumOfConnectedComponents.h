 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFCONNECTEDCOMPONENTS.JAVA_H
#define CGTEA_NUMOFCONNECTEDCOMPONENTS.JAVA_H

#include "ReportInterface.h"

class ConnectedComponents : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Connected Components";
    };
    string description() override {
        return "number of connected componentes";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_NUMOFCONNECTEDCOMPONENTS.JAVA_H
