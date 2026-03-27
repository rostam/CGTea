// Created by rostam on 10.10.19.
#ifndef CGTEA_ADDITIVEHARARY_H
#define CGTEA_ADDITIVEHARARY_H
#include "ReportInterface.h"

// Additive Harary Index: AH(G) = sum_{uv in E} 1/(deg_u + deg_v)
class AdditiveHararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        double ah = 0.0;
        for_each_e_const(g, [&](Edge e) {
            int du = boost::out_degree(boost::source(e, g), g);
            int dv = boost::out_degree(boost::target(e, g), g);
            if (du + dv > 0)
                ah += 1.0 / (du + dv);
        });
        return std::to_string(ah);
    }
    string name()        const override { return "Additive Harary Index"; }
    string description() const override { return "sum_{uv in E} 1/(deg_u+deg_v)"; }
    string type()        const override { return "double"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
