 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_RANDOM_H
#define CGTEA_RANDOM_H

#include "GeneratorInterface.h"

class Random : public GeneratorInterface {
public:
    explicit Random() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < numOfEdges; i++)
            ret[i] = randomEdge();

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() const override {
        return "Random Graph";
    }

    string description() const override {
        return "Generates a random graph with N Vertices and E Edges";
    }
    
    string category() const override {
        return "Random Graphs";
    };
    
    string check_parameters() override {
    	if( numOfEdges<0 || n<0) return "Both Edges & Vertices must be positive!";
    	else return "";
    };
};

#endif

