 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WIENERPOLARITYINDEX_H
#define CGTEA_WIENERPOLARITYINDEX_H

#include "ReportInterface.h"

class WienerPolarityIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Wiener Polarity Index";
    };
    string description() const override {
        return "Wiener Polarity Index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "Topological Indices";
    };
};

#endif //CGTEA_WIENERPOLARITYINDEX_H
