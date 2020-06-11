 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_CIRCLE_H
#define CGTEA_CIRCLE_H

#include "GeneratorInterface.h"

class Circle : public GeneratorInterface {
public:
    explicit Circle() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, g);
        }
        add_edge(n-1,0, g);
        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
    }

    string name() override {
        return "Circle";
    }

    string description() override {
        return "Genrates a Circle(Cn)";
    }
    
    string category() override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        if (n < 0) return "n must be positive";
        else return null;
    };
};

#endif

