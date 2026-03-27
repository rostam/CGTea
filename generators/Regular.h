//
// Created by rostam on 18.10.19.
//

#ifndef CGTEA_REGULAR_H
#define CGTEA_REGULAR_H

#include "GeneratorInterface.h"

class Regular : public GeneratorInterface {
public:
    explicit Regular() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        int t = 0;
        if (k % 2 == 0) {
            for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = i + 1; j < i + (k / 2) + 1; j++) {
                    if (i != j) {
                        add_edge(i, j % n, 1, g);
                    }
                }
            }
        } else {
            for (unsigned int i = 0; i < n; i = i + 1) {
                for (unsigned int j = i + 1; j < i + ((k - 1) / 2) + 1; j++) {
                    add_edge(i, j % n, 1, g);
                }

                for (unsigned int j = i - 1; j > i - ((k - 1) / 2) - 1; j--) {
                    add_edge(i, (j + n) % n, 1, g);
                }
            }

            for (unsigned int i = 0; i < n / 2; i++) {
                add_edge(i, (i + (n / 2)) % n, 1, g);
            }
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            boost::put(boost::vertex_distance, g, v, pos[i]);
            i++;
        });
        return g;
    }

    bool hasSecondParam()  const override { return true; }
    string paramNName()    const override { return "n (vertices)"; }
    string paramKName()    const override { return "k (degree)"; }
    unsigned int defaultN() const override { return 6; }
    unsigned int defaultK() const override { return 3; }

    string name() const override {
        return "Regular";
    }

    string description() const override {
        return "Generates a regular graph.";
    }
};

#endif //CGTEA_REGULAR_H
