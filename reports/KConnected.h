 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_KCONNECTED.JAVA_H
#define CGTEA_KCONNECTED.JAVA_H

#include "ReportInterface.h"

class VertexConnectivity : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Vertex Connectivity";
    };
    string description() override {
        return "Vertex Connectivity";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "Connectivity";
    };
};

#endif //CGTEA_KCONNECTED.JAVA_H
