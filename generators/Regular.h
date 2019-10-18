//
// Created by rostam on 18.10.19.
//

#ifndef CGTEA_REGULAR_H
#define CGTEA_REGULAR_H

#include "GeneratorInterface.h"

class Regular : public GeneratorInterface {
public:
    explicit Regular() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int deg) override {
        Graph g;
        int t = 0;
        if (deg % 2 == 0) {
            for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = i + 1; j < i + (deg / 2) + 1; j++) {
                    if (i != j) {
                        add_edge(i, j % n, g);
                    }
                }
            }
        } else {
            for (unsigned int i = 0; i < n; i = i + 1) {
                for (unsigned int j = i + 1; j < i + ((deg - 1) / 2) + 1; j++) {
                    add_edge(i, j % n, g);
                }

                for (unsigned int j = i - 1; j > i - ((deg - 1) / 2) - 1; j--) {
                    add_edge(i, (j + n) % n, g);
                }
            }

            for (unsigned int i = 0; i < n / 2; i++) {
                add_edge(i, (i + (n / 2)) % n, g);
            }
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        cerr << "drin" << endl;
        cerr << n << "," << k << endl;
        Graph g;// = generate(n, k);
//        cerr << n << "," << k << endl;
//        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
//        int i = 0;
//        for_each_v(g, [&](Ver v) {
//            boost::put(boost::vertex_distance, g, v, pos[i]);
//            i++;
//        });
        return g;
    }

    string name() override {
        return "Regular";
    }

    string description() override {
        return "Generates a regular graph.";
    }
};

#endif //CGTEA_REGULAR_H