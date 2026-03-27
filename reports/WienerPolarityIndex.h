// Created by rostam on 10.10.19.
#ifndef CGTEA_WIENERPOLARITYINDEX_H
#define CGTEA_WIENERPOLARITYINDEX_H
#include "ReportInterface.h"
#include "Utils.h"

// W_P(G) = # unordered pairs {u,v} with d(u,v) = 3
class WienerPolarityIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 3) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        int wp = 0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] == 3) wp++;
        return std::to_string(wp);
    }
    string name()        const override { return "Wiener Polarity Index"; }
    string description() const override { return "# pairs at distance exactly 3"; }
    string type()        const override { return "int"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
