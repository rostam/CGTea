//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_DENSITY_H
#define CGTEA_DENSITY_H

#include "ReportInterface.h"

class Density : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0.000000";
        double d = 2.0 * boost::num_edges(g) / ((double)n * (n - 1));
        return std::to_string(d);
    }
    string name() const override { return "Density"; }
    string description() const override { return "Edge density: 2m / (n*(n-1))"; }
    string type() const override { return "double"; }
    string category() const override { return "General"; }
};

#endif //CGTEA_DENSITY_H
