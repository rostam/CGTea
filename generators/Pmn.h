 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_PMN_H
#define CGTEA_PMN_H

#include "GeneratorInterface.h"

class Pmn : public GeneratorInterface {
public:
    explicit Pmn() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (j < m - 1) {
                     add_edge(i * m + j, i * m + j + 1, g);
                    
                }
                if (i < n - 1) {
                     add_edge(i * m + j, (i + 1, g) * (m, g) + j, g);
                    
                }
            }
        
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() const override {
        return "Pm * Pn";
    }

    string description() const override {
        return "Generate Pm*Pn";
    }
    
    string category() const override {
        return "General Graphs";
    };
    
    string check_parameters() override {
    	if(n<0 || m<0)return "Both m & n must be positive!";
    	else return "";
    };
};

#endif

