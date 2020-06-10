 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_PATH_H
#define CGTEA_PATH_H

#include "GeneratorInterface.h"

class Path : public GeneratorInterface {
public:
    explicit Path() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, g);
        }

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, g);
        }
        
        return g;
    }

    string name() override {
        return "Path";
    }

    string description() override {
        return "Generates a path with n vertices";
    }
    
    string category() override {
        return "Trees";
    };
    
    string check_parameters() override {
    	if (n < 0) return "n must be positive";
        else return null;
    };
};

#endif

