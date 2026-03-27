// Created by rostam on 10.10.19.
#ifndef CGTEA_MOSTARINDEX_H
#define CGTEA_MOSTARINDEX_H
#include "ReportInterface.h"
#include "Utils.h"

// Mo(G) = sum_{uv in E} |n_u(e) - n_v(e)|
// n_u(e) = # vertices strictly closer to u than to v
class MostarIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n == 0) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        long long mo = 0;
        for_each_e_const(g, [&](Edge e) {
            int u = boost::source(e, g);
            int v = boost::target(e, g);
            int nu = 0, nv = 0;
            for (int w = 0; w < n; w++) {
                if (dist[w][u] < dist[w][v]) nu++;
                else if (dist[w][v] < dist[w][u]) nv++;
            }
            mo += std::abs(nu - nv);
        });
        return std::to_string(mo);
    }
    string name()        const override { return "Mostar Index"; }
    string description() const override { return "Mo = sum_{uv in E} |n_u - n_v|"; }
    string type()        const override { return "int"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
