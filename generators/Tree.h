 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_TREE_H
#define CGTEA_TREE_H

#include "GeneratorInterface.h"

class Tree : public GeneratorInterface {
public:
    explicit Tree() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        n = (int) ((Math.pow(degree, depth + 1) - 1) / (degree - 1));
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i + 1, i / degree, g);
        }
        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        n = (int) ((Math.pow(degree, depth + 1) - 1) / (degree - 1));
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i + 1, i / degree, g);
        }
        

    }

    string name() const override {
        return "Complete Tree";
    }

    string description() const override {
        return "Generates a complete tree";
    }
    
    string category() const override {
        return "Trees";
    };
    
    string check_parameters() override {
        
    	if(depth<0 || degree<0)return" Both depth & degree must be positive!";
    	else
    		return null;
   
    };
};

#endif

