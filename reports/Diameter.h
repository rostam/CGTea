 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DIAMETER_H
#define CGTEA_DIAMETER_H

#include "ReportInterface.h"
#include "Utils.h"


class GraphDiameter : public ReportInterface {
public:
    string report(const Graph& g) override {
        DistanceMatrix dist = Utils::get_floyd_warshall_all_pairs_shortest_paths(g);
        int max = 0;
        int num_v = boost::num_vertices(g);
        for (int v = 0; v < num_v; v++) {
            for (int u = 0; u < num_v; u++) {
                if(dist[v][u] < num_v) {
                    int distance = dist[u][v];
                    if(distance > max) {
                        max = distance;
                    }
                }
            }
        }
        return std::to_string(max);
    };
    string name() override {
        return "Graph Diameter";
    };
    string description() override {
        return "Graph Diameter";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "General";
    };
};

#endif //CGTEA_DIAMETER.JAVA_H
