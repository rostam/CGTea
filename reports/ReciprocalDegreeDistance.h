// Created by rostam on 10.10.19.
#ifndef CGTEA_RECIPROCALDEGREEDISTANCE_H
#define CGTEA_RECIPROCALDEGREEDISTANCE_H
#include "ReportInterface.h"
#include "Utils.h"

// RDD(G) = sum_{u<v} (deg_u + deg_v) / d(u,v)
class ReciprocalDegreeDistance : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_vertices(g);
        if (n <= 1) return "0.000000";
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        double rdd = 0.0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (dist[u][v] > 0 && dist[u][v] < n)
                    rdd += (boost::out_degree(u, g) + boost::out_degree(v, g))
                           / (double)dist[u][v];
        return std::to_string(rdd);
    }
    string name()        const override { return "Reciprocal Degree Distance"; }
    string description() const override { return "RDD = sum_{u<v} (deg_u+deg_v)/d(u,v)"; }
    string type()        const override { return "double"; }
    string category()    const override { return "Topological Indices"; }
};
#endif
