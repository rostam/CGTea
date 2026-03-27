// Created by rostam on 10.10.19.
#ifndef CGTEA_MWIENERINDEX_H
#define CGTEA_MWIENERINDEX_H
#include "ReportInterface.h"
#include "Utils.h"
#include <cmath>

// Multiplicative Wiener Index: WPi(G) = prod_{u<v} d(u,v)
// Returned as log value (ln) to avoid overflow on larger graphs.
class MultiplicativeWienerIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0.000000";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        double logSum = 0.0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] > 0 && dist[u][v] < n)
                    logSum += std::log(dist[u][v]);
        return std::to_string(logSum);
    }
    string name()        const override { return "Multiplicative Wiener Index (log)"; }
    string description() const override { return "ln(prod_{u<v} d(u,v))"; }
    string type()        const override { return "double"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
