 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_COCKTAILPARTY_H
#define CGTEA_COCKTAILPARTY_H

#include "GeneratorInterface.h"
/**
 * @brief CocktailParty Graph
 * - Reference: https://mathworld.wolfram.com/CocktailPartyGraph.html
 * - A graph consisting of two rows of paired nodes in which all nodes 
 *   except the paired ones are connected with straight lines
 * - So called because it can be visualised as the set of handshakes 
 *   if n couples go to a party and each person shakes hands with every person except his or her partner. 
 * 
 */
class CocktailParty : public GeneratorInterface {
public:
    explicit CocktailParty() : GeneratorInterface() {};


    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g;


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                 add_edge(i, n + j, g);
                 add_edge(i,j, g);
                 add_edge(n+i,n+j, g);
                
            }
        }
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, 2*n);
        
        for_each_v(g, [&](Ver v) {boost::put(boost::vertex_distance, g, v, pos[v]);});
        return g;
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
    	return "";
    };
};

#endif

