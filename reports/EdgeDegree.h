// Created by rostam on 10.10.19.
#ifndef CGTEA_EDGEDEGREE_H
#define CGTEA_EDGEDEGREE_H
#include "ReportInterface.h"

// Sum of (deg(u)+deg(v)) over all edges uv
class EdgeDegree : public ReportInterface {
public:
    string report(const Graph& g) override {
        long long ed = 0;
        for_each_e_const(g, [&](Edge e) {
            ed += boost::out_degree(boost::source(e, g), g)
                + boost::out_degree(boost::target(e, g), g);
        });
        return std::to_string(ed);
    }
    string name()        const override { return "Edge Degree Sum"; }
    string description() const override { return "sum_{uv in E} (deg_u + deg_v)"; }
    string type()        const override { return "int"; }
    string category()    const override { return "General"; }
};
#endif
