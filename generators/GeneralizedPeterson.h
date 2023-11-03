/**
 * Created by rostami on 28.06.17.
*/
#ifndef EXACT_COLORING_GENERALIZEDPETERSONGENERATOR_H
#define EXACT_COLORING_GENERALIZEDPETERSONGENERATOR_H

#include "GeneratorInterface.h"

class GeneralizedPeterson : public GeneratorInterface {
public:
    Graph generate(unsigned int n, unsigned int k) {
        Graph g;
        for (int i = 0; i < n; i++) {
            add_edge((i % n), ((i + 1) % n), 1, g);
            add_edge((i % n), ((i + n) % (2 * n)), 1, g);
            if (i + n + k > 2 * n - 1)
                add_edge(((i + n) % (2 * n)), ((i + n + k) % (2 * n)) + n, 1, g);
            else
                add_edge(((i + n) % (2 * n)), ((i + n + k) % (2 * n)), 1, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos1 = position_generators::circle(width, height, 100.0, n);
        std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(width, height, 200.0, n);
        int i = 0;
        for_each_v(g, [&](Ver v) {
            if(i < n) boost::put(boost::vertex_distance, g, v, pos2[i]);
            else      boost::put(boost::vertex_distance, g, v, pos1[i - n]);
            i++;
        });
        return g;
    }

    string name() const override {
        return "Generalized Peterson";
    }

    string description() const override {
        return "Generates a generalized peterson graph.";
    }

    string category() const override {
        return "General";
    }
};

#endif //EXACT_COLORING_GENERALIZEDPETERSONGENERATOR_H
