 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_FLOWER_H
#define CGTEA_FLOWER_H

#include "GeneratorInterface.h"

class Flower : public GeneratorInterface {
public:
    explicit Flower() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++) {
            add_edge(i, n + i, 1, g);
            add_edge(n + i, 2 * n, 1, g);
            add_edge(n + i, n + ((i + 1) % n), 1, g);
            add_edge(i, 2 * n, 1, g);
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos1 = position_generators::circle(width, height, 150.0, n);
        std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(width, height, 250.0, n);
        boost::put(boost::vertex_distance, g, 0, cgtea_geometry::Point(width / 2, height / 2));
        int i = 0;
        for_each_v(g, [&](Ver v) {
            if (v <= n && v > 0) boost::put(boost::vertex_distance, g, v, pos1[i + 1]);
            else if (v > n) boost::put(boost::vertex_distance, g, v, pos2[i + 1]);
            i++;
        });
        return g;
    }

    string name() const override {
        return "Flower Graph";
    }

    string description() const override {
        return "Generate Flower Graph";
    }
    
    string category() const override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        return "";
    };
};

#endif

