//
// Created by rostam on 27.03.26.
//

#include "Radius.h"
#include "Utils.h"

string GraphRadius::report(const Graph& g) {
    int n = boost::num_vertices(g);
    if (n == 0) return "0";
    DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
    int radius = n;
    for (int v = 0; v < n; v++) {
        int ecc = 0;
        for (int u = 0; u < n; u++) {
            if (u != v && dist[v][u] < n && dist[v][u] > ecc)
                ecc = dist[v][u];
        }
        if (ecc < radius) radius = ecc;
    }
    return std::to_string(radius);
}
