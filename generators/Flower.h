 
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
            add_edge(i, n + i, g);
            add_edge(n + i, 2 * n, g);
            add_edge(n + i, n + ((i + 1, g) % n, g), g);
            add_edge(i, 2 * n, g);
        }
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() override {
        return "Flower Graph";
    }

    string description() override {
        return "Generate Flower Graph";
    }
    
    string category() override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        return "";
    };
};

#endif

