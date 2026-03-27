//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_AVERAGEDEGREE_H
#define CGTEA_AVERAGEDEGREE_H

#include "ReportInterface.h"

class AverageDegree : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n == 0) return "0.000000";
        return std::to_string(2.0 * boost::num_edges(g) / n);
    }
    string name() const override { return "Average Degree"; }
    string description() const override { return "Average vertex degree (2m/n)"; }
    string type() const override { return "double"; }
    string category() const override { return "General"; }
};

#endif //CGTEA_AVERAGEDEGREE_H
