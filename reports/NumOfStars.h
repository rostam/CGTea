// Created by rostam on 10.10.19.
#ifndef CGTEA_NUMOFSTARS_H
#define CGTEA_NUMOFSTARS_H
#include "ReportInterface.h"

// Number of star subgraphs K_{1,k} for all k >= 2.
// Counts C(deg(v),2) per vertex = cherries (2-paths) centered at v.
class NumberOfStars : public ReportInterface {
public:
    string report(const Graph& g) override {
        long long stars = 0;
        for_each_v_const(g, [&](Ver v) {
            long long d = boost::out_degree(v, g);
            stars += d * (d - 1) / 2;
        });
        return std::to_string(stars);
    }
    string name()        const override { return "Number of Stars"; }
    string description() const override { return "sum_v C(deg(v),2)"; }
    string type()        const override { return "int"; }
    string category()    const override { return "General"; }
};
#endif
