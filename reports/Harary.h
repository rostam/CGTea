// Created by rostam on 10.10.19.
#ifndef CGTEA_HARARY_H
#define CGTEA_HARARY_H
#include "ReportInterface.h"
#include "Utils.h"

// H(G) = sum_{u<v} 1/d(u,v)
class HararyIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0.000000";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        double h = 0.0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] > 0 && dist[u][v] < n)
                    h += 1.0 / dist[u][v];
        return std::to_string(h);
    }
    string name()        const override { return "Harary Index"; }
    string description() const override { return "H = sum_{u<v} 1/d(u,v)"; }
    string type()        const override { return "double"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
