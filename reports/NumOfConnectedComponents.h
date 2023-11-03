 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFCONNECTEDCOMPONENTS_H
#define CGTEA_NUMOFCONNECTEDCOMPONENTS_H

#include "ReportInterface.h"

class ConnectedComponents : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Connected Components";
    };
    string description() const override {
        return "number of connected componentes";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_NUMOFCONNECTEDCOMPONENTS_H
