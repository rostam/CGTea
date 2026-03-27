// Created by rostam on 27.03.26.
#ifndef CGTEA_FRIENDSHIPGRAPH_H
#define CGTEA_FRIENDSHIPGRAPH_H
#include "GeneratorInterface.h"

// Friendship graph F_n: n triangles sharing a single common vertex (vertex 0)
// Total vertices: 2n + 1
class FriendshipGraph : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (unsigned int i = 0; i < n; i++) {
            unsigned int a = 2 * i + 1;
            unsigned int b = 2 * i + 2;
            add_edge(0, a, g);
            add_edge(0, b, g);
            add_edge(a, b, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        // hub at center
        boost::put(boost::vertex_distance, g, 0, cgtea_geometry::Point(width, height));
        // pairs of triangle vertices arranged evenly around the hub
        auto pts = position_generators::circle(width, height, 160.0, 2 * n);
        for (unsigned int i = 0; i < 2 * n; i++)
            boost::put(boost::vertex_distance, g, i + 1, pts[i]);
        return g;
    }

    string name()        const override { return "Friendship Graph"; }
    string description() const override { return "n triangles sharing one vertex"; }
    string paramNName()  const override { return "n (triangles)"; }
    unsigned int defaultN() const override { return 4; }
};
#endif
