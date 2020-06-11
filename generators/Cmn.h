 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_CMN_H
#define CGTEA_CMN_H

#include "GeneratorInterface.h"

class Cmn : public GeneratorInterface {
public:
    explicit Cmn() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j > m - 2)
                     add_edge(i * m + j, i * m, 1, g);
                else
                     add_edge(i * m + j, i * m + j + 1, 1, g);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > n - 2)
                     add_edge(i * m + j, j, 1, g);
                else
                     add_edge(i * m + j, (i + 1, g) * m + j, 1, g);
                
            }
        }


        

    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        return g;
    }

    string name() override {
        return "Cm * Cn";
    }

    string description() override {
        return "Generate Cm*Cn";
    }
    
    string category() override {
        return "General Graphs";
    };
    
    string check_parameters() override {
        
    	if ( n<0 || m<0)return"Both m & n must be positive!";
    	else
    		return null;
   
    };
};

#endif

