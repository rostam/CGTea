 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_TADPOLE_H
#define CGTEA_TADPOLE_H

#include "GeneratorInterface.h"

class Tadpole : public GeneratorInterface {
public:
    explicit Tadpole() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, g);
        }
        add_edge(n-1,0, g);
         add_edge(1,n, g);
        for(int i=n+1;i<n+k;i++) {
             add_edge(i-1,i, g);
        }
        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        
        for (int i = 0; i < n - 1; i++) {
             add_edge(i, i + 1, g);
        }
        add_edge(n-1,0, g);
         add_edge(1,n, g);
        for(int i=n+1;i<n+k;i++) {
             add_edge(i-1,i, g);
        }
        

    }

    string name() const override {
        return "Tadpole Graph";
    }

    string description() const override {
        return "Genrates a Tadpole";
    }
    
    string category() const override {
        return "General Graphs";
    };
    
    string check_parameters() override {
        
        if (n < 0) return "n must be positive";
        else
            return null;
   
    };
};

#endif

