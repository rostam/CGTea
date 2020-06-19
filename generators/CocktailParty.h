 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_COCKTAILPARTY_H
#define CGTEA_COCKTAILPARTY_H

#include "GeneratorInterface.h"

class CocktailParty : public GeneratorInterface {
public:
    explicit CocktailParty() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                 add_edge(i, n + j, g);
                 add_edge(i,j, g);
                 add_edge(n+i,n+j, g);
            }
        }
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                 add_edge(i, n + j, g);
                 add_edge(i,j, g);
                 add_edge(n+i,n+j, g);
                
            }
        }
    }

    string name() const override {
        return "CockTail Party Graph";
    }

    string description() const override {
        return "CockTail Party Graph";
    }
    
    string category() const override {
        return "General Graphs";
    };
    
    string check_parameters() override {
    	return null;
    };
};

#endif

