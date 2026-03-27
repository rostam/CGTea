// Created by rostam on 10.10.19.
#ifndef CGTEA_TOTALECCENTRITYINDEX_H
#define CGTEA_TOTALECCENTRITYINDEX_H
#include "ReportInterface.h"
#include "Utils.h"

// xi(G) = sum_v ecc(v),   ecc(v) = max_u d(u,v)
class TotalEccentricityIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        long long total = 0;
        for (int u = 0; u < n; u++) {
            int ecc = 0;
            for (int v = 0; v < n; v++)
                if (dist[u][v] < n && dist[u][v] > ecc)
                    ecc = dist[u][v];
            total += ecc;
        }
        return std::to_string(total);
    }
    string name()        const override { return "Total Eccentricity Index"; }
    string description() const override { return "xi = sum_v ecc(v)"; }
    string type()        const override { return "int"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
