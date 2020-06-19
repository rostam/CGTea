 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_KCONNECTED_H
#define CGTEA_KCONNECTED_H

#include "ReportInterface.h"

class VertexConnectivity : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Vertex Connectivity";
    };
    string description() const override {
        return "Vertex Connectivity";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Connectivity";
    };
};

#endif //CGTEA_KCONNECTED_H
