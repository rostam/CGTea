// Created by rostam on 10.10.19.
#ifndef CGTEA_DEGREEDISTANCE_H
#define CGTEA_DEGREEDISTANCE_H
#include "ReportInterface.h"
#include "Utils.h"

// D'(G) = sum_{u<v} (deg(u) + deg(v)) * d(u,v)
class DegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        long long dd = 0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] < n)
                    dd += (long long)(boost::out_degree(u, g) + boost::out_degree(v, g)) * dist[u][v];
        return std::to_string(dd);
    }
    string name()        const override { return "Degree Distance"; }
    string description() const override { return "D' = sum_{u<v} (deg_u + deg_v) * d(u,v)"; }
    string type()        const override { return "int"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
