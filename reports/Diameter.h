 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DIAMETER_H
#define CGTEA_DIAMETER_H

#include "ReportInterface.h"
#include "boost/graph/floyd_warshall_shortest.hpp"
#include <boost/graph/exterior_property.hpp>

class GraphDiameter : public ReportInterface {
public:
    string report(const Graph& g) override {
        typedef boost::exterior_vertex_property<Graph, int> DistanceProperty;
        typedef DistanceProperty::matrix_type DistanceMatrix;
        typedef DistanceProperty::matrix_map_type DistanceMatrixMap;
        DistanceMatrix distances(num_vertices(g));
        DistanceMatrixMap dm(distances, g);
        floyd_warshall_all_pairs_shortest_paths(g,dm);
        cout << boost::num_vertices(g) << endl;
        for_each_v_const(g, [&](const Ver& v) {
            for_each_v_const(g, [&](const Ver& u) {
                cout << v << " " << u << " " << distances[v][u] << endl;
            });
        });

//        int n = boostt::num_edges(g);
        return std::to_string(10);
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
