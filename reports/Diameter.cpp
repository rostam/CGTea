 
//
// Created by rostam on 10.10.19.
//

#include "Diameter.h"

std::string GraphDiameter::report(const Graph& g) {
    DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
    int max = 0;
    int num_v = boost::num_vertices(g);
    for (int v = 0; v < num_v; v++) {
        for (int u = 0; u < num_v; u++) {
            if (dist[v][u] < num_v) {
                int distance = dist[u][v];
                if (distance > max) {
                    max = distance;
                }
            }
        }
    }
    return std::to_string(max);
};
