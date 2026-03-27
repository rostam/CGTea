//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_WIENERINDEX_H
#define CGTEA_WIENERINDEX_H

#include "ReportInterface.h"
#include "Utils.h"

class WienerIndex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n == 0) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        long long total = 0;
        for (int v = 0; v < n; v++)
            for (int u = v + 1; u < n; u++)
                if (dist[v][u] < n)
                    total += dist[v][u];
        return std::to_string(total);
    }
    string name() const override { return "Wiener Index"; }
    string description() const override { return "Sum of all pairwise shortest-path distances"; }
    string type() const override { return "int"; }
    string category() const override { return "Topological Indices"; }
};

#endif //CGTEA_WIENERINDEX_H
