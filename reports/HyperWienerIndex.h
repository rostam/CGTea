// Created by rostam on 10.10.19.
#ifndef CGTEA_HYPERWIENERINDEX_H
#define CGTEA_HYPERWIENERINDEX_H
#include "ReportInterface.h"
#include "Utils.h"

// WW(G) = (1/2) * sum_{u<v} [ d(u,v) + d(u,v)^2 ]
class HyperWienerIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        long long ww = 0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] < n) {
                    long long d = dist[u][v];
                    ww += d + d * d;
                }
        return std::to_string(ww / 2);
    }
    string name()        const override { return "Hyper Wiener Index"; }
    string description() const override { return "WW = (1/2)*sum_{u<v}[d+d^2]"; }
    string type()        const override { return "int"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
