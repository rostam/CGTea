/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"

class Cycle : public GeneratorInterface {
public:
    Cycle(int n) : GeneratorInterface(n) {};
    Graph generate(bool fill_positions = false) {
        Graph g;
        for (int i = 0; i < n; i++)
            add_edge(i, ((i + 1) % n),g);
        if(fill_positions) {
            std::vector<std::pair<double,double>> pos = position_generators::circle(300,300,300,n);
            int i=0;
            for_each_v(g, [&](Ver v) {
                boost::put(boost::vertex_distance, g, v, pos[i]);
                i++;
            });
        }
        return g;
    }
};

#endif
