 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_CROWN_H
#define CGTEA_CROWN_H

#include "GeneratorInterface.h"

class Crown : public GeneratorInterface {
public:
    explicit Crown() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++) {
            add_edge(i, n + i, 1, g);
            add_edge(n + i, 2 * n, 1, g);
            add_edge(n + i, n + ((i + 1, g) % n, g), 1, g);

        }
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() override {
        return "Crown Graph";
    }

    string description() override {
        return "Generate Crown Graph";
    }
    
    string category() override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        if( n<3) return "n must be higher than 2!";
        else return null;
    }
};

#endif

